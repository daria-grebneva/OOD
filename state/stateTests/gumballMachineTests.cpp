#include "stdafx.h"
#include "../state/CHasQuarterState.cpp"
#include "../state/CHasQuarterState.h"
#include "../state/CNoQuarterState.cpp"
#include "../state/CNoQuarterState.h"
#include "../state/CSoldOutState.cpp"
#include "../state/CSoldOutState.h"
#include "../state/CSoldState.cpp"
#include "../state/CSoldState.h"
#include "../state/GumBallMachineWithState.cpp"
#include "../state/GumBallMachineWithState.h"

std::string MachineState(unsigned gumBalls, std::string state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % gumBalls % (gumBalls != 1 ? "s" : "") % state).str();
}

void CheckStateOutput(const CGumballMachine& machine, unsigned gumBalls, std::string state)
{
	REQUIRE(machine.ToString() == MachineState(gumBalls, state));
}

std::string turnACrankState = "waiting for turn of crank";
std::string soldOutState = "sold out";
std::string waitingQuarterState = "waiting for quarter";

TEST_CASE("CNoQuarterState", "[CNoQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;

	SECTION("check insert quarter")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState);
	}

	SECTION("check eject quarter")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, waitingQuarterState);
	}

	SECTION("check turn crank")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\nYou need to pay first\n");
		CheckStateOutput(machine, gumballsNumber, waitingQuarterState);
	}
}

TEST_CASE("CHasQuarterState", "[CHasQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;

	CGumballMachine machine(gumballsNumber, out);
	machine.InsertQuarter();

	SECTION("check insert quarter")
	{
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\nYou can't insert another quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState);
	}

	SECTION("check eject quarter")
	{
		machine.EjectQuarter();
		REQUIRE(out.str() == "You inserted a quarter\nQuarter returned\n");
		CheckStateOutput(machine, gumballsNumber, waitingQuarterState);
	}

	SECTION("check turn crank")
	{
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
		CheckStateOutput(machine, gumballsNumber - 1, waitingQuarterState);
	}

	SECTION("check turn crank with a last gumball")
	{
		std::stringstream out;
		CGumballMachine machine(1, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
		CheckStateOutput(machine, 0, soldOutState);
	}
}

TEST_CASE("CSoldOutState", "[CSoldOutState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 0;

	SECTION("check insert quarter")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState);
	}

	SECTION("check eject quarter")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState);
	}

	SECTION("check turn crank")
	{
		CGumballMachine machine(gumballsNumber, out);
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\nNo gumball dispensed\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState);
	}
}
