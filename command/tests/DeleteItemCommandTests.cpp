#include "stdafx.h"
#include "../command/DeleteItemCommand.h"
#include "../command/History.h"
#include "../command/Image.h"
#include "../command/InsertImageCommand.h"
#include "Constants.h"

TEST_CASE("CDeleteItemCommand", "[CDeleteItemCommand]")
{
	CHistory history;
	std::vector<CDocumentItem> items;

	SECTION("check execute delete item")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		insertImage->Execute();
		REQUIRE_FALSE(items.empty());
		auto deleteItem = std::make_unique<CDeleteItemCommand>(items, 0);
		deleteItem->Execute();
		REQUIRE(items.empty());
	}

	SECTION("check unexecute delete item")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		insertImage->Execute();
		REQUIRE_FALSE(items.empty());
		auto deleteItem = std::make_unique<CDeleteItemCommand>(items, 0);
		deleteItem->Execute();
		REQUIRE(items.empty());
		deleteItem->Unexecute();
		REQUIRE_FALSE(items.empty());
	}

	SECTION("can not delete image when it in history")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		insertImage->Execute();
		auto img = items.front().GetImage();
		REQUIRE(boost::filesystem::exists(img->GetPath()));

		auto deleteItem = std::make_unique<CDeleteItemCommand>(items, 0);
		deleteItem->Execute();
		REQUIRE(boost::filesystem::exists(img->GetPath()));
	}

	SECTION("delete image when it is not in history")
	{
		auto insertImage = std::make_unique<CInsertImageCommand>(history, items, IMAGE_PATH, 100, 100, "images", 0);
		insertImage->Execute();
		auto img = items.front().GetImage();
		REQUIRE(boost::filesystem::exists(img->GetPath()));

		auto deleteItem = std::make_unique<CDeleteItemCommand>(items, 0);
		deleteItem->Execute();
		deleteItem.reset();

		REQUIRE_FALSE(boost::filesystem::exists(img->GetPath()));
	}
}
