#include "stdafx.h"
#include "../WheatherStationStats/Observer.h"
#include "../WheatherStationStats/WheatherData.h"

using namespace std;

class Observable : public CObservable<int>
{
protected:
	int GetChangedData() const override
	{
		return 0;
	}
};

namespace NotifyObservers
{
class Observer : public IObserver<int>
{
public:
	void SetObserverAndObservableForRemove(Observer& observer, Observable& observable)
	{
		m_observerForRemove = &observer;
		m_observableForRemove = &observable;
	}

private:
	Observer* m_observerForRemove;
	Observable* m_observableForRemove;
	void Update(const int& data) override
	{
		data;
		m_observableForRemove->RemoveObserver(*m_observerForRemove);
	}
};

void CheckNotifyObservers(Observer& a, Observer& b)
{
	Observable observable;
	observable.RegisterObserver(a, 0);
	observable.RegisterObserver(b, 1);
	a.SetObserverAndObservableForRemove(a, observable);
	b.SetObserverAndObservableForRemove(b, observable);

	REQUIRE_NOTHROW(observable.NotifyObservers());
	REQUIRE_NOTHROW(observable.NotifyObservers());
}
} // namespace NotifyObservers

namespace NotifyPriority
{
class Observer : public IObserver<int>
{
public:
	void SetNotificationsOutput(vector<IObserver<int>*>& output)
	{
		m_notificationsOutput = &output;
	}

private:
	vector<IObserver<int>*>* m_notificationsOutput;
	void Update(const int& data) override
	{
		data;
		m_notificationsOutput->push_back(this);
	}
};
} // namespace NotifyPriority

TEST_CASE(" ", "[CObserver]")
{
	SECTION("Notify observers when observer remove another observer while updating")
	{
		NotifyObservers::Observer observer1;
		NotifyObservers::Observer observer2;

		NotifyObservers::CheckNotifyObservers(observer1, observer2);
		NotifyObservers::CheckNotifyObservers(observer1, observer1);
		NotifyObservers::CheckNotifyObservers(observer2, observer2);
		NotifyObservers::CheckNotifyObservers(observer2, observer1);
	}

	SECTION("Notify observers by their priority")
	{

		vector<IObserver<int>*> notifications;
		REQUIRE(notifications == vector<IObserver<int>*>());

		vector<NotifyPriority::Observer> observers;
		observers.assign(4, NotifyPriority::Observer());
		for (auto& current : observers)
		{
			current.SetNotificationsOutput(notifications);
		}

		Observable observable;
		observable.RegisterObserver(observers[0], 2);
		observable.RegisterObserver(observers[1], 4);
		observable.RegisterObserver(observers[2], 3);
		observable.NotifyObservers();

		REQUIRE(notifications == vector<IObserver<int>*>({ &observers[0], &observers[2], &observers[1] }));
		notifications.clear();
		observable.RegisterObserver(observers[3], 1);
		observable.NotifyObservers();
		REQUIRE(notifications == vector<IObserver<int>*>({ &observers[3], &observers[0], &observers[2], &observers[1] }));
	}
}
