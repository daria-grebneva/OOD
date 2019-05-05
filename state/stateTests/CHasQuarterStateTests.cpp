#include "stdafx.h"
#include "../state/CHasQuarterState.cpp"
#include "../state/CHasQuarterState.h"
#include "../state/IGumballMachine.h"
#include "../state/IState.h"

namespace CHasQuarterStateTests
{
class CGumballMachineTest : public IGumballMachine
{
public:
	CGumballMachineTest(unsigned numBalls, std::stringstream& output)
		: m_count(numBalls)
		, m_out(output){};

private:
	unsigned GetBallCount() const override { return 0; };
	void ReleaseBall() override{};
	void SetSoldOutState() override{};
	void SetNoQuarterState() override{};
	void SetSoldState() override{};
	void SetHasQuarterState() override{};

private:
	unsigned m_count = 0;
	IState* m_state;
	std::stringstream& m_out;
};
} // namespace CHasQuarterStateTests

TEST_CASE("when gumball machine HasQuarterState", "[CHasQuarterState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 10;

	CHasQuarterStateTests::CGumballMachineTest machine(gumballsNumber, out);
	CHasQuarterState hasQuarterState(machine, out);

	SECTION("inserting quarter can not insert quarter")
	{
		hasQuarterState.InsertQuarter();
		REQUIRE(out.str() == "You can't insert another quarter\n");
	}

	SECTION("ejecting quarter return quarter")
	{
		hasQuarterState.EjectQuarter();
		REQUIRE(out.str() == "Quarter returned\n");
	}

	SECTION("dispensing can not dispense gumballs")
	{
		hasQuarterState.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("can turn a crank")
	{
		hasQuarterState.TurnCrank();
		REQUIRE(out.str() == "You turned...\n");
	}

	SECTION("to string show waiting for turn of crank message")
	{
		auto str = hasQuarterState.ToString();
		REQUIRE(str == "waiting for turn of crank");
	}
}
