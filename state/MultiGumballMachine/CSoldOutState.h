#pragma once
#include "IGumballMachine.h"
#include "IState.h"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine, std::stringstream& output);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;
	void Refill(unsigned gumBallsCount);

private:
	IGumballMachine& m_gumballMachine;
	std::stringstream& m_out;
};
