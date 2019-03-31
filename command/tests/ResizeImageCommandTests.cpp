#include "stdafx.h"
#include "../command/ResizeImageCommand.h"

TEST_CASE("CResizeImage", "[CResizeImage]")
{
	int currentWidth = 100;
	int currentHeight = 150;
	int width = 200;
	int height = 300;

	SECTION("check execute resize")
	{
		auto resizeCommand = std::make_unique<CResizeImageCommand>(currentWidth, width, currentHeight, height);
		resizeCommand->Execute();

		REQUIRE(currentWidth == width);
		REQUIRE(currentHeight == height);
	}

	SECTION("check unexecute resize")
	{
		auto resizeCommand = std::make_unique<CResizeImageCommand>(currentWidth, width, currentHeight, height);
		resizeCommand->Execute();
		resizeCommand->Unexecute();

		REQUIRE_FALSE(currentWidth == width);
		REQUIRE_FALSE(currentHeight == height);
	}
}
