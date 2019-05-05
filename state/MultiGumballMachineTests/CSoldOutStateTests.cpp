#include "stdafx.h"
#include "../MultiGumballMachine/CSoldOutState.cpp"
#include "../MultiGumballMachine/CSoldOutState.h"
#include "../MultiGumballMachine/IGumballMachine.h"
#include "../MultiGumballMachine/IState.h"

namespace CSoldOutStateTests
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

	void AddQuarter() override
	{
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			++m_quartersCount;
		}
	};

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
} // namespace CSoldOutStateTests

TEST_CASE("when gumball machine SoldOutState", "[CSoldOutState]")
{

	std::stringstream out;
	unsigned gumballsNumber = 2;

	CSoldOutStateTests::CMultiGumballMachineTest machine(gumballsNumber, out);
	CSoldOutState soldOutState(machine, out);

	SECTION("can refill gumballs")
	{
		REQUIRE(machine.GetBallCount() == 2);
		soldOutState.Refill(10);
		REQUIRE(machine.GetBallCount() == 12);
	}

	SECTION("inserting quarter can not insert quarter")
	{
		soldOutState.InsertQuarter();
		REQUIRE(out.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("when have no quarter can not eject a quarter")
	{
		soldOutState.EjectQuarter();
		REQUIRE(out.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("when have quarters ejecting quarter return all of quarters")
	{
		machine.AddQuarter();
		machine.AddQuarter();
		soldOutState.EjectQuarter();
		REQUIRE(out.str() == "Quarter returned\nQuarter returned\n");
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
