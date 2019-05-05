#include "stdafx.h"
#include "../MultiGumballMachine/CNoQuarterState.cpp"
#include "../MultiGumballMachine/CNoQuarterState.h"
#include "../MultiGumballMachine/IGumballMachine.h"
#include "../MultiGumballMachine/IState.h"

namespace CNoQuarterStateTests
{
class CMultiGumballMachineTest : public IGumballMachine
{
public:
	CMultiGumballMachineTest(unsigned numBalls, std::stringstream& output)
		: m_gumBallsCount(numBalls)
		, m_out(output){};

	void Refill(unsigned gumBallsCount) override
	{
		m_gumBallsCount += gumBallsCount;
	};

	unsigned GetBallCount() const override { return m_gumBallsCount; };
	unsigned GetQuartersCount() override { return m_quartersCount; };

private:
	void ReleaseBall() override{};
	void AddBall(unsigned gumBallsCount) override
	{
		m_gumBallsCount += gumBallsCount;
	};
	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

	void AddQuarter() override
	{
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
		}
	};
	void RemoveQuarter() override
	{
		if (m_quartersCount != 0)
		{
			--m_quartersCount;
		}
	};

private:
	const unsigned MAX_QUARTERS_COUNT = 5;
	unsigned m_gumBallsCount = 0;
	unsigned m_quartersCount = 0;
	IState* m_state;
	std::stringstream& m_out;
};
} // namespace CNoQuarterStateTests

TEST_CASE("when gumball machine NoQuarterState", "[CNoQuarterStateTests]")
{

	std::stringstream out;
	unsigned gumballsNumber = 2;

	CNoQuarterStateTests::CMultiGumballMachineTest machine(gumballsNumber, out);
	CNoQuarterState noQuarterState(machine, out);

	SECTION("can refill gumballs")
	{
		REQUIRE(machine.GetBallCount() == 2);
		noQuarterState.Refill(10);
		REQUIRE(machine.GetBallCount() == 12);
	}

	SECTION("inserting quarter can always insert quarter")
	{
		noQuarterState.InsertQuarter();
		REQUIRE(out.str() == "");
	}

	SECTION("can not eject a quarter")
	{
		noQuarterState.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
	}

	SECTION("dispensing can not dispense gumballs")
	{
		noQuarterState.Dispense();
		REQUIRE(out.str() == "You need to pay first\n");
	}

	SECTION("can not turn a crank")
	{
		noQuarterState.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\n");
	}

	SECTION("to string show waiting for quarter message")
	{
		auto str = noQuarterState.ToString();
		REQUIRE(str == "waiting for quarter");
	}
}
