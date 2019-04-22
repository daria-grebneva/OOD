#include "stdafx.h"
#include "CMultiGumballMachine.h"

CMultiGumballMachine::CMultiGumballMachine(unsigned numBalls, std::stringstream& output)
	: m_soldState(*this, output)
	, m_soldOutState(*this, output)
	, m_noQuarterState(*this, output)
	, m_hasQuarterState(*this, output)
	, m_state(&m_soldOutState)
	, m_gumBallsCount(numBalls)
	, m_out(output)
{
	if (m_gumBallsCount > 0)
	{
		m_state = &m_noQuarterState;
	}
}
void CMultiGumballMachine::EjectQuarter()
{
	m_state->EjectQuarter();
}
void CMultiGumballMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}
void CMultiGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}
std::string CMultiGumballMachine::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Quarters: %4%
)");
	return (fmt % m_gumBallsCount % (m_gumBallsCount != 1 ? "s" : "") % m_state->ToString() % m_quartersCount).str();
}

unsigned CMultiGumballMachine::GetBallCount() const
{
	return m_gumBallsCount;
}

void CMultiGumballMachine::ReleaseBall()
{
	if (m_gumBallsCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_gumBallsCount;
	}
}

void CMultiGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}

void CMultiGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}

void CMultiGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}

void CMultiGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}

void CMultiGumballMachine::AddBall(unsigned gumBallsCount)
{
	m_gumBallsCount += gumBallsCount;
	m_out << "+ " << gumBallsCount << " of gum balls\n";
}

unsigned CMultiGumballMachine::GetQuartersCount()
{
	return m_quartersCount;
}

void CMultiGumballMachine::AddQuarter()
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

void CMultiGumballMachine::RemoveQuarter()
{
	if (m_quartersCount != 0)
	{
		--m_quartersCount;
	}
}

void CMultiGumballMachine::Refill(unsigned gumBallsCount)
{
	m_state->Refill(gumBallsCount);
}
