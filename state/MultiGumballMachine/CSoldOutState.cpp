#include "stdafx.h"
#include "CSoldOutState.h"
#include "IGumballMachine.h"

CSoldOutState::CSoldOutState(IGumballMachine& gumballMachine, std::stringstream& output)
	: m_gumballMachine(gumballMachine)
	, m_out(output)
{
}

void CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}
void CSoldOutState::EjectQuarter()
{
	if (m_gumballMachine.GetQuartersCount() == 0)
	{
		m_out << "You can't eject, you haven't inserted a quarter yet\n";
	}
	else
	{
		while (m_gumballMachine.GetQuartersCount() != 0)
		{
			m_gumballMachine.RemoveQuarter();
			m_out << "Quarter returned\n";
		}
	}
}
void CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
}
void CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
}
std::string CSoldOutState::ToString() const
{
	return "sold out";
}

void CSoldOutState::Refill(unsigned gumBallsCount)
{
	m_gumballMachine.AddBall(gumBallsCount);

	if (m_gumballMachine.GetBallCount() != 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
}
