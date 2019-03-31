#include "stdafx.h"
#include "../command/History.h"
#include "../command/Image.h"
#include "../command/InsertImageCommand.h"
#include "Constants.h"

TEST_CASE("CInsertImage", "[CInsertImage]")
{
	CHistory history;
	std::vector<CDocumentItem> items;

	SECTION("check insert image")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		REQUIRE(items.empty());
		insertImage->Execute();
		REQUIRE_FALSE(items.empty());
	}

	SECTION("check execute")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		REQUIRE(items.empty());
		insertImage->Execute();
		REQUIRE_FALSE(items.empty());
		insertImage->Unexecute();
		REQUIRE(items.empty());
	}

	SECTION("check create path of image")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		REQUIRE(items.empty());
		insertImage->Execute();

		auto img = items.front().GetImage();
		REQUIRE(boost::filesystem::exists(img->GetPath()));
	}

	SECTION("check delete image when execute")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		REQUIRE(items.empty());
		insertImage->Execute();

		auto img = items.front().GetImage();
		REQUIRE(boost::filesystem::exists(img->GetPath()));
		insertImage->Unexecute();
		insertImage.reset();
		REQUIRE_FALSE(boost::filesystem::exists(img->GetPath()));
	}

	SECTION("can not insert image with wrong file extension")
	{
		std::string path = boost::filesystem::change_extension(IMAGE_PATH, ".doc").string();
		REQUIRE_THROWS(std::make_unique<CInsertImageCommand>(history, items, path, 100, 100, "images", 0));
	}

	SECTION("can not insert image with wrong position")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 5);
		REQUIRE_THROWS(insertImage->Execute());
	}

	SECTION("can not insert image with wrong path")
	{
		REQUIRE_THROWS(std::make_unique<CInsertImageCommand>(history, items, "E:/3.jpg", 100, 100, "images", 0));
	}
}
