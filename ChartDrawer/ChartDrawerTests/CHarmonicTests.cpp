#include "pch.h"

#include "../ChartDrawer/CHarmonic.cpp"
#include "../ChartDrawer/CHarmonic.h"
#define _USE_MATH_DEFINES

TEST_CASE("CHarmonic", "[CHarmonic]")
{
	auto harmonic = new CHarmonic(0, 0, 0, HarmonicType::Sin);

	SECTION("update amplitude when set amplitude")
	{
		REQUIRE(harmonic->GetAmplitude() == 0);
		harmonic->SetAmplitude(10.5);
		REQUIRE(harmonic->GetAmplitude() == 10.5);
	}

	SECTION("update frequency when set frequency")
	{
		REQUIRE(harmonic->GetFrequency() == 0);
		harmonic->SetFrequency(10.5);
		REQUIRE(harmonic->GetFrequency() == 10.5);
	}

	SECTION("update phase when set phase")
	{
		REQUIRE(harmonic->GetPhase() == 0);
		harmonic->SetPhase(10.5);
		REQUIRE(harmonic->GetPhase() == 10.5);
	}

	SECTION("update function type when set function type")
	{
		REQUIRE(harmonic->GetHarmonicType() == HarmonicType::Sin);
		harmonic->SetHarmonicType(HarmonicType::Cos);
		REQUIRE(harmonic->GetHarmonicType() == HarmonicType::Cos);
	}

	SECTION("calculate function value type when calculate value")
	{
		harmonic->SetAmplitude(2.0);
		harmonic->SetFrequency(0.5);
		harmonic->SetPhase(0.0);
		harmonic->SetHarmonicType(HarmonicType::Sin);
		REQUIRE(harmonic->CalculateValue(atan(1) * 4) == 2.0);
	}
}
