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
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_out << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}

std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}
