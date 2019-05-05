#include "stdafx.h"
#include "../MultiGumballMachine/CHasQuarterState.cpp"
#include "../MultiGumballMachine/CHasQuarterState.h"
#include "../MultiGumballMachine/IGumballMachine.h"
#include "../MultiGumballMachine/IState.h"

namespace CHasQuarterStateTests
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
} // namespace CHasQuarterStateTests

TEST_CASE("when gumball machine HasQuarterState", "[CHasQuarterState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 2;

	CHasQuarterStateTests::CMultiGumballMachineTest machine(gumballsNumber, out);
	CHasQuarterState hasQuarterState(machine, out);

	SECTION("can refill gumballs")
	{
		REQUIRE(machine.GetBallCount() == 2);
		hasQuarterState.Refill(10);
		REQUIRE(machine.GetBallCount() == 12);
	}

	SECTION("inserting quarter can always insert quarter")
	{
		hasQuarterState.InsertQuarter();
		REQUIRE(out.str() == "");
	}

	SECTION("ejecting quarter when have no quarter doesn't return anything")
	{
		hasQuarterState.EjectQuarter();
		REQUIRE(out.str() == "");
	}

	SECTION("ejecting quarter return all of quarters")
	{
		hasQuarterState.InsertQuarter();
		hasQuarterState.InsertQuarter();
		hasQuarterState.EjectQuarter();
		REQUIRE(out.str() == "Quarter returned\nQuarter returned\n");
	}

	SECTION("dispensing can not dispense gumballs")
	{
		hasQuarterState.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("turning a crank decreases the number of quarters")
	{
		hasQuarterState.InsertQuarter();
		REQUIRE(machine.GetQuartersCount() == 1);
		hasQuarterState.TurnCrank();
		REQUIRE(machine.GetQuartersCount() == 0);
		REQUIRE(out.str() == "You turned...\n");
	}

	SECTION("to string show waiting for turn of crank message")
	{
		auto str = hasQuarterState.ToString();
		REQUIRE(str == "waiting for turn of crank");
	}
}
