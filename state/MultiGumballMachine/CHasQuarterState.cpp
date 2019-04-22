#include "stdafx.h"
#include "CHasQuarterState.h"

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine, std::stringstream& output)
	: m_gumballMachine(gumballMachine)
	, m_out(output)
{
}

void CHasQuarterState::Refill(unsigned gumBallsCount)
{
	m_gumballMachine.AddBall(gumBallsCount);
}

void CHasQuarterState::InsertQuarter()
{
	m_gumballMachine.AddQuarter();
}

void CHasQuarterState::EjectQuarter()
{
	while (m_gumballMachine.GetQuartersCount() != 0)
	{
		m_gumballMachine.RemoveQuarter();
		m_out << "Quarter returned\n";
	}

	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	if (m_gumballMachine.GetQuartersCount() != 0)
	{
		m_gumballMachine.RemoveQuarter();
	}
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}
