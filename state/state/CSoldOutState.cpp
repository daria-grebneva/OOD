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
	m_out << "You can't eject, you haven't inserted a quarter yet\n";
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
