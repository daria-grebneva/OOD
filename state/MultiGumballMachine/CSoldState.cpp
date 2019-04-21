#include "stdafx.h"
#include "CSoldState.h"

CSoldState::CSoldState(IGumballMachine& gumballMachine, std::stringstream& output)
	: m_gumballMachine(gumballMachine)
	, m_out(output)
{
}

void CSoldState::InsertQuarter()
{
	m_out << "Please wait, we're already giving you a gumball\n";
}

void CSoldState::EjectQuarter()
{
	m_out << "Sorry you already turned the crank\n";
}

void CSoldState::TurnCrank()
{
	m_out << "Turning twice doesn't get you another gumball\n";
}

void CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	m_gumballMachine.RemoveQuarter();

	if ((m_gumballMachine.GetBallCount() == 0) && (m_gumballMachine.GetQuartersCount() == 0))
	{
		m_gumballMachine.SetSoldOutState();
	}
	else if (m_gumballMachine.GetBallCount() == 0)
	{
		m_out << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else if (m_gumballMachine.GetQuartersCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
}

std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}

void CSoldState::Refill(unsigned gumBallsCount)
{
	m_out << "can not refill when giving a gum" << std::endl;
}
