#include "stdafx.h"
#include "../state/CSoldOutState.cpp"
#include "../state/CSoldOutState.h"
#include "../state/IGumballMachine.h"
#include "../state/IState.h"

namespace CSoldOutStateTests
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
} // namespace CSoldOutStateTests

TEST_CASE("when gumball machine SoldOutState", "[CSoldOutState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 10;

	CSoldOutStateTests::CGumballMachineTest machine(gumballsNumber, out);
	CSoldOutState soldOutState(machine, out);

	SECTION("inserting quarter can not insert quarter")
	{
		soldOutState.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("ejecting quarter can not return quarter")
	{
		soldOutState.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("dispensing can not dispense gumballs")
	{
		soldOutState.Dispense();
		REQUIRE(out.str() == "No gumball dispensed\n");
	}

	SECTION("can not turn a crank")
	{
		soldOutState.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\n");
	}

	SECTION("to string show sold out message")
	{
		auto str = soldOutState.ToString();
		REQUIRE(str == "sold out");
	}
}
