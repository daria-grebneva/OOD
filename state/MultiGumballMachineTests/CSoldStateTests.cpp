#include "stdafx.h"
#include "../MultiGumballMachine/CSoldState.cpp"
#include "../MultiGumballMachine/CSoldState.h"
#include "../MultiGumballMachine/IGumballMachine.h"
#include "../MultiGumballMachine/IState.h"

namespace CSoldStateTests
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
} // namespace CSoldStateTests

TEST_CASE("when gumball machine SoldStateTests", "[CSoldStateTests]")
{
	std::stringstream out;
	unsigned gumballsNumber = 2;

	CSoldStateTests::CMultiGumballMachineTest machine(gumballsNumber, out);
	CSoldState soldState(machine, out);

	SECTION("can not refill gumballs")
	{
		soldState.Refill(10);
		REQUIRE(out.str() == "can not refill when giving a gum\n");
	}

	SECTION("can not insert quarter")
	{
		soldState.InsertQuarter();
		REQUIRE(out.str() == "Please wait, we're already giving you a gumball\n");
	}

	SECTION("can not eject a quarter")
	{
		soldState.EjectQuarter();
		REQUIRE(out.str() == "Sorry you already turned the crank\n");
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

	SECTION("when gumball number less than 1 can not dispense")
	{

		std::stringstream out;
		unsigned gumballsNumber = 0;

		CSoldStateTests::CMultiGumballMachineTest machine(gumballsNumber, out);
		CSoldState soldState(machine, out);
		soldState.Dispense();
		REQUIRE(out.str() == "Oops, out of gumballs\n");
	}

	SECTION("when gumball number more than 0 can dispense")
	{
		soldState.Dispense();
		REQUIRE(out.str() == "");
	}
}
