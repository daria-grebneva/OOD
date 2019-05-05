#include "stdafx.h"
#include "../state/CNoQuarterState.cpp"
#include "../state/CNoQuarterState.h"
#include "../state/IGumballMachine.h"
#include "../state/IState.h"

namespace CNoQuarterStateTests
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
} // namespace CNoQuarterStateTests

TEST_CASE("when gumball machine NoQuarterState", "[CNoQuarterState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 10;

	CNoQuarterStateTests::CGumballMachineTest machine(gumballsNumber, out);
	CNoQuarterState noQuarterState(machine, out);

	SECTION("inserting quarter can insert quarter")
	{
		noQuarterState.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
	}

	SECTION("ejecting quarter return error")
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
