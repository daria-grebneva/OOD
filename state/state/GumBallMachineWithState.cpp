#include "stdafx.h"
#include "GumBallMachineWithState.h"

CGumballMachine::CGumballMachine(unsigned numBalls, std::stringstream& output)
	: m_soldState(*this, output)
	, m_soldOutState(*this, output)
	, m_noQuarterState(*this, output)
	, m_hasQuarterState(*this, output)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
	, m_out(output)
{
	if (m_count > 0)
	{
		m_state = &m_noQuarterState;
	}
}
void CGumballMachine::EjectQuarter()
{
	m_state->EjectQuarter();
}
void CGumballMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}
void CGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}
std::string CGumballMachine::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_count;
}

void CGumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}
void CGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}
void CGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}
void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}
void CGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}
