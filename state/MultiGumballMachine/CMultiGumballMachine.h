#pragma once
#include "CHasQuarterState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"
#include "IGumballMachine.h"
#include "IState.h"

class CMultiGumballMachine : private IGumballMachine
{
public:
	CMultiGumballMachine(unsigned numBalls, std::stringstream& output);

	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	std::string ToString() const;
	void Refill(unsigned gumBallsCount) override;

private:
	unsigned GetBallCount() const override;
	void ReleaseBall() override;
	void AddBall(unsigned gumBallsCount) override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	void AddQuarter() override;
	void RemoveQuarter() override;
	unsigned GetQuartersCount() override;

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_gumBallsCount = 0;
	unsigned m_quartersCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
	std::stringstream& m_out;
};
