#pragma once

#include <boost/format.hpp>
#include <iostream>
#include <sstream>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	CGumballMachine(unsigned count, std::stringstream& output)
		: m_gumBallsCount(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		, m_out(output)
		, m_quartersCount(0)
	{
	}

	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			AddQuarter();
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			AddQuarter();
			break;
		case State::Sold:
			m_out << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::HasQuarter:
			while (m_quartersCount != 0)
			{
				RemoveQuarter();
				m_out << "Quarter returned\n";
			}

			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			m_out << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_out << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (m_quartersCount == 0)
			{
				m_out << "You can't eject, you haven't inserted a quarter yet\n";
			}
			else
			{
				while (m_quartersCount != 0)
				{
					RemoveQuarter();
					m_out << "Quarter returned\n";
				}
			}
			break;
		}
	}

	void TurnCrank()
	{
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			m_out << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			m_out << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			m_out << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_gumBallsCount = numBalls;
		if (m_gumBallsCount > 0)
		{
			m_state = State::NoQuarter;
		}
		if (m_quartersCount > 0)
		{
			m_state = State::HasQuarter;
		}
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter" : (m_state == State::HasQuarter) ? "waiting for turn of crank" : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Quarters: %4%
)");
		return (fmt % m_gumBallsCount % (m_gumBallsCount != 1 ? "s" : "") % state % m_quartersCount).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			m_out << "A gumball comes rolling out the slot...\n";
			--m_gumBallsCount;
			RemoveQuarter();

			if (m_gumBallsCount == 0)
			{
				m_out << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else if (m_quartersCount == 0)
			{
				m_state = State::NoQuarter;
			}
			else
			{
				m_state = State::HasQuarter;
			}

			break;
		case State::NoQuarter:
			m_out << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			m_out << "No gumball dispensed\n";
			break;
		}
	}

	void AddQuarter()
	{
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
			m_out << "You inserted a quarter\n";
		}
		else
		{
			m_out << "Max number of quarters!\n";
		}
	}

	void RemoveQuarter()
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	}

	unsigned m_gumBallsCount; // Количество шариков
	unsigned m_quartersCount;
	const unsigned MAX_QUARTERS_COUNT = 5;
	State m_state = State::SoldOut;
	std::stringstream& m_out;
};
} // namespace naive
