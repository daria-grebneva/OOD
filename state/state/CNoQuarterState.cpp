#include "stdafx.h"
#include "CNoQuarterState.h"
#include "IState.h"

CNoQuarterState::CNoQuarterState(IGumballMachine& gumballMachine, std::stringstream& output)
	: m_gumballMachine(gumballMachine)
	, m_out(output)
{
}

void CNoQuarterState::InsertQuarter()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
}
void CNoQuarterState::EjectQuarter()
{
	m_out << "You haven't inserted a quarter\n";
}
void CNoQuarterState::TurnCrank()
{
	m_out << "You turned but there's no quarter\n";
}
void CNoQuarterState::Dispense()
{
	m_out << "You need to pay first\n";
}
std::string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}
