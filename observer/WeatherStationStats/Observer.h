#pragma once

#include <functional>
#include <map>
#include <set>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned int priority) override
	{
		m_priorities.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto priorities = m_priorities;
		for (auto current : priorities)
		{
			(current.second)->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto current : m_priorities)
		{
			if (current.second == &observer)
			{
				m_priorities.erase(current.first);
				break;
			}
		}
	}

protected:
	// ������-���������� ������ ����������� ������ �����,
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData() const = 0;

private:
	std::multimap<unsigned int, ObserverType*> m_priorities;
};
