#pragma once
#include "CHasQuarterState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"
#include "IGumballMachine.h"
#include "IState.h"

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls, std::stringstream& output);

	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	std::string ToString() const;

private:
	unsigned GetBallCount() const override;
	void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

private:
	unsigned m_count = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
	std::stringstream& m_out;
};
