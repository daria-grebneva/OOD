#include "stdafx.h"
#include "../state/CSoldState.cpp"
#include "../state/CSoldState.h"
#include "../state/IGumballMachine.h"
#include "../state/IState.h"

namespace CSoldStateTests
{
class CGumballMachineTest : public IGumballMachine
{
public:
	CGumballMachineTest(unsigned numBalls, std::stringstream& output)
		: m_count(numBalls)
		, m_out(output){};

private:
	unsigned GetBallCount() const override { return m_count; };
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
} // namespace CSoldStateTests

TEST_CASE("when gumball machine SoldState", "[CSoldState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 10;

	CSoldStateTests::CGumballMachineTest machine(gumballsNumber, out);
	CSoldState soldState(machine, out);

	SECTION("inserting quarter can not insert quarter")
	{
		soldState.InsertQuarter();
		REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
	}

	SECTION("ejecting quarter can not return quarter")
	{
		soldState.EjectQuarter();
		REQUIRE(out.str() == "Sorry you already turned the crank\n");
	}

	SECTION("dispensing can dispense gumballs")
	{
		soldState.Dispense();
		REQUIRE(out.str() == "");
	}

	SECTION("dispensing show out of gumballs message")
	{

		std::stringstream out;
		unsigned gumballsNumber = 0;

		CSoldStateTests::CGumballMachineTest machine(gumballsNumber, out);
		CSoldState soldState(machine, out);
		soldState.Dispense();
		REQUIRE(out.str() == "Oops, out of gumballs\n");
	}

	SECTION("can not turn a crank")
	{
		soldState.TurnCrank();
		REQUIRE(out.str() == "Turning twice doesn't get you another gumball\n");
	}

	SECTION("to string show delivering a gumball message")
	{
		auto str = soldState.ToString();
		REQUIRE(str == "delivering a gumball");
	}
}
