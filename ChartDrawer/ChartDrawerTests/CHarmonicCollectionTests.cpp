#include "pch.h"

//#include "../ChartDrawer/CHarmonic.cpp"
//#include "../ChartDrawer/CHarmonic.h"
#include "../ChartDrawer/CHarmonicCollection.cpp"
#include "../ChartDrawer/CHarmonicCollection.h"

TEST_CASE("CHarmonicCollection", "[CHarmonicCollection]")
{
	/*auto harmonic1 = new CHarmonic(1, 0.5, 0, HarmonicType::Sin);
	auto harmonic2 = new CHarmonic(1, 0.5, 0, HarmonicType::Sin);
	auto harmonic3 = new CHarmonic(1, 0.5, 0, HarmonicType::Sin);*/

	auto collection = new CHarmonicCollection();

	SECTION("can not get harmonic when there is no harmonic")
	{
		REQUIRE(collection->GetHarmonicsCount() == 0);
		REQUIRE_THROWS(collection->GetHarmonic(0));
	}

	SECTION("can not delete harmonic when there is no harmonic")
	{
		REQUIRE(collection->GetHarmonicsCount() == 0);
		REQUIRE_THROWS(collection->DeleteHarmonic(0));
	}

	SECTION("can add harmonic")
	{
		REQUIRE(collection->GetHarmonicsCount() == 0);
		collection->AddHarmonic(1, 0.5, 4, HarmonicType::Cos);
		REQUIRE(collection->GetHarmonicsCount() == 1);
		auto harmonic = collection->GetHarmonic(0);
		REQUIRE(harmonic->GetAmplitude() == 1);
		REQUIRE(harmonic->GetFrequency() == 0.5);
		REQUIRE(harmonic->GetPhase() == 4);
		REQUIRE(harmonic->GetHarmonicType() == HarmonicType::Cos);
	}

	SECTION("can delete harmonic after adding")
	{
		REQUIRE(collection->GetHarmonicsCount() == 0);
		collection->AddHarmonic(1, 0.5, 4, HarmonicType::Cos);
		collection->AddHarmonic(1, 0.5, 4, HarmonicType::Cos);
		REQUIRE(collection->GetHarmonicsCount() == 2);
		collection->DeleteHarmonic(1);
		REQUIRE(collection->GetHarmonicsCount() == 1);
	}

	SECTION("can calculate value of all harmonics")
	{
		REQUIRE(collection->GetHarmonicsCount() == 0);
		collection->AddHarmonic(1, 0.5, 0.0, HarmonicType::Cos);
		collection->AddHarmonic(4, 0.5, 0.0, HarmonicType::Sin);
		auto value = collection->CalculateValue(atan(1) * 4);
		REQUIRE(value == 4);
	}
}
