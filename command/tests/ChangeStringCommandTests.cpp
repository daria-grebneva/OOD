#include "stdafx.h"
#include "../command/ChangeStringCommand.h"

TEST_CASE("CChangeStringCommand", "[CChangeStringCommand]")
{
	std::string oldString = "old string";
	std::string newString = "new string";

	SECTION("check execute change string")
	{
		auto changeString = std::make_unique<CChangeStringCommand>(oldString, newString);
		changeString->Execute();
		REQUIRE(oldString == newString);
	}

	SECTION("check unexecute change string")
	{
		auto changeString = std::make_unique<CChangeStringCommand>(oldString, newString);
		changeString->Execute();
		changeString->Unexecute();
		REQUIRE_FALSE(oldString == newString);
	}
}
