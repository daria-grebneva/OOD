#pragma once
#include "IGumballMachine.h"
#include "IState.h"

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine, std::stringstream& output);
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
	std::stringstream& m_out;
};
