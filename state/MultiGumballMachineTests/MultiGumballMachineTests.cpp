#include "stdafx.h"
#include "../MultiGumballMachine/CHasQuarterState.cpp"
#include "../MultiGumballMachine/CHasQuarterState.h"
#include "../MultiGumballMachine/CMultiGumballMachine.cpp"
#include "../MultiGumballMachine/CMultiGumballMachine.h"
#include "../MultiGumballMachine/CNoQuarterState.cpp"
#include "../MultiGumballMachine/CNoQuarterState.h"
#include "../MultiGumballMachine/CSoldOutState.cpp"
#include "../MultiGumballMachine/CSoldOutState.h"
#include "../MultiGumballMachine/CSoldState.cpp"
#include "../MultiGumballMachine/CSoldState.h"
#include "../MultiGumballMachine/NaiveGumBallMachine.h"

std::string MachineState(unsigned gumBalls, std::string state, unsigned quarters)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Quarters: %4%
)");
	return (fmt % gumBalls % (gumBalls != 1 ? "s" : "") % state % quarters).str();
}

void CheckStateOutput(const CMultiGumballMachine& machine, unsigned gumBalls, std::string state, unsigned quarters)
{
	REQUIRE(machine.ToString() == MachineState(gumBalls, state, quarters));
}

std::string turnACrankState = "waiting for turn of crank";
std::string soldOutState = "sold out";
std::string quarterState = "waiting for quarter";

TEST_CASE("CSoldOutState", "[CSoldOutState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 0;
	unsigned quartersNumber = 0;
	CMultiGumballMachine machine(gumballsNumber, out);

	SECTION("check insert quarter")
	{
		machine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}

	SECTION("check eject quarter")
	{
		machine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}

	SECTION("check turn crank")
	{
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\nNo gumball dispensed\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}

	SECTION("check refill")
	{
		machine.Refill(5);
		REQUIRE(out.str() == "+ 5 of gum balls\n");
		CheckStateOutput(machine, 5, quarterState, quartersNumber);
	}

	SECTION("check refill when soldout")
	{
		machine.Refill(0);
		REQUIRE(out.str() == "+ 0 of gum balls\n");
		CheckStateOutput(machine, 0, soldOutState, quartersNumber);
	}
}

TEST_CASE("CNoQuarterState", "[CNoQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;
	CMultiGumballMachine machine(gumballsNumber, out);

	SECTION("check insert quarter")
	{
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState, 1);
	}

	SECTION("check eject quarter")
	{
		machine.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check turn crank")
	{
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\nYou need to pay first\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check refill")
	{
		machine.Refill(5);
		REQUIRE(out.str() == "+ 5 of gum balls\n");
		CheckStateOutput(machine, 15, quarterState, 0);
	}

	SECTION("check refill when soldout")
	{
		CMultiGumballMachine machine(0, out);
		machine.Refill(0);
		REQUIRE(out.str() == "+ 0 of gum balls\n");
		CheckStateOutput(machine, 0, soldOutState, 0);
	}

	SECTION("check inserting more than five quarters")
	{
		CMultiGumballMachine machine(10, out);
		for (unsigned i = 0; i < 6; ++i)
		{
			machine.InsertQuarter();
		}

		REQUIRE(out.str() == "You inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nMax number of quarters!\n");
		CheckStateOutput(machine, 10, turnACrankState, 5);
	}
}

TEST_CASE("CHasQuarterState", "[CHasQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;

	SECTION("check insert quarter")
	{
		CMultiGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState, 1);
	}

	SECTION("check eject quarter")
	{
		CMultiGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		machine.EjectQuarter();
		REQUIRE(out.str() == "You inserted a quarter\nQuarter returned\nQuarter returned\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check turn crank")
	{
		CMultiGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, gumballsNumber - 1, quarterState, 0);
	}

	SECTION("check turn crank with last gum")
	{
		CMultiGumballMachine machine(1, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, 0, soldOutState, 0);
	}

	SECTION("check turn crank with last quarter")
	{
		std::stringstream out;
		CMultiGumballMachine machine(2, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, 1, quarterState, 0);
	}

	SECTION("check refill")
	{
		CMultiGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		machine.Refill(5);
		REQUIRE(out.str() == "You inserted a quarter\n+ 5 of gum balls\n");
		CheckStateOutput(machine, 15, turnACrankState, 1);
	}

	SECTION("check refill when soldout")
	{
		CMultiGumballMachine machine(0, out);
		machine.InsertQuarter();
		machine.Refill(0);
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n+ 0 of gum balls\n");
		CheckStateOutput(machine, 0, soldOutState, 0);
	}
}

void CheckStateOutput(const naive::CGumballMachine& machine, unsigned gumBalls, std::string state, unsigned quarters)
{
	REQUIRE(machine.ToString() == MachineState(gumBalls, state, quarters));
}

TEST_CASE("naive::CSoldOutState", "[naive::CSoldOutState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 0;
	unsigned quartersNumber = 0;
	naive::CGumballMachine machine(gumballsNumber, out);

	SECTION("check insert quarter")
	{
		machine.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}

	SECTION("check eject quarter")
	{
		machine.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}

	SECTION("check turn crank")
	{
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no gumballs\n");
		CheckStateOutput(machine, gumballsNumber, soldOutState, quartersNumber);
	}
}

TEST_CASE("naive::CNoQuarterState", "[naive::CNoQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;
	naive::CGumballMachine machine(gumballsNumber, out);

	SECTION("check insert quarter")
	{
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState, 1);
	}

	SECTION("check eject quarter")
	{
		machine.EjectQuarter();
		REQUIRE(out.str() == "You haven't inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check turn crank")
	{
		machine.TurnCrank();
		REQUIRE(out.str() == "You turned but there's no quarter\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check inserting more than five quarters")
	{
		naive::CGumballMachine machine(10, out);
		for (unsigned i = 0; i < 6; ++i)
		{
			machine.InsertQuarter();
		}

		REQUIRE(out.str() == "You inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nYou inserted a quarter\nMax number of quarters!\n");
		CheckStateOutput(machine, 10, turnACrankState, 5);
	}
}

TEST_CASE("naive::CHasQuarterState", "[naive::CHasQuarterState]")
{
	std::stringstream out;
	unsigned gumballsNumber = 10;

	SECTION("check insert quarter")
	{
		naive::CGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		REQUIRE(out.str() == "You inserted a quarter\n");
		CheckStateOutput(machine, gumballsNumber, turnACrankState, 1);
	}

	SECTION("check eject quarter")
	{
		naive::CGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		machine.EjectQuarter();
		REQUIRE(out.str() == "You inserted a quarter\nQuarter returned\n");
		CheckStateOutput(machine, gumballsNumber, quarterState, 0);
	}

	SECTION("check turn crank")
	{
		naive::CGumballMachine machine(gumballsNumber, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, gumballsNumber - 1, quarterState, 0);
	}

	SECTION("check turn crank with last gum")
	{
		naive::CGumballMachine machine(1, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, 0, soldOutState, 0);
	}

	SECTION("check turn crank with last quarter")
	{
		naive::CGumballMachine machine(2, out);
		machine.InsertQuarter();
		machine.TurnCrank();
		REQUIRE(out.str() == "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nQuarter returned\n");
		CheckStateOutput(machine, 1, quarterState, 0);
	}
}
