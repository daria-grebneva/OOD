#include "stdafx.h"
#include "../WeatherStationStats/Observer.h"
#include "../WeatherStationStats/WeatherData.h"

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
	void CDisplayNotification(Observer& observer, Observable& observable)
	{
		m_observer = &observer;
		m_observable = &observable;
	}

private:
	Observer* m_observer;
	Observable* m_observable;
	void Update(const int& data) override
	{
		data;
		m_observable->RemoveObserver(*m_observer);
	}
};
} // namespace NotifyObservers

namespace NotifyPriority
{
class Observer : public IObserver<int>
{
public:
	void SetNotificationsByPriority(vector<IObserver<int>*>& output)
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
		NotifyObservers::Observer a;

		Observable observable;
		observable.RegisterObserver(a, 0);
		a.CDisplayNotification(a, observable);

		REQUIRE_NOTHROW(observable.NotifyObservers());
	}

	SECTION("Notify observers by their priority")
	{
		vector<IObserver<int>*> notifications;
		REQUIRE(notifications == vector<IObserver<int>*>());

		vector<NotifyPriority::Observer> observers;
		
		NotifyPriority::Observer a, b, c;
		Observable observable;
		observable.RegisterObserver(a, 1);
		a.SetNotificationsByPriority(notifications);
		observable.RegisterObserver(b, 2);
		b.SetNotificationsByPriority(notifications);
		observable.NotifyObservers();

		REQUIRE(notifications == vector<IObserver<int>*>({ &a, &b }));
		notifications.clear();
		observable.RegisterObserver(c, 0);
		c.SetNotificationsByPriority(notifications);
		observable.NotifyObservers();
		REQUIRE(notifications == vector<IObserver<int>*>({ &c, &a, &b }));
	}
}