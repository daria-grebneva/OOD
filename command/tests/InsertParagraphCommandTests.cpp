#include "stdafx.h"
#include "../command/History.h"
#include "../command/InsertParagraphCommand.h"
#include "../command/Paragraph.h"

TEST_CASE("CInsertParagraph", "[CInsertParagraph]")
{
	CHistory history;
	std::string text = "<!-- the title -->";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;

	SECTION("check execute with set position")
	{
		auto insertParagraph = std::make_unique<CInsertParagraphCommand>(paragraph, items, 0);
		REQUIRE(items.empty());
		insertParagraph->Execute();

		REQUIRE_FALSE(items.empty());
	}

	SECTION("check execute with end position")
	{
		auto insertParagraph = std::make_unique<CInsertParagraphCommand>(paragraph, items, boost::none);
		REQUIRE(items.empty());
		insertParagraph->Execute();

		REQUIRE_FALSE(items.empty());
	}

	SECTION("check unexecute")
	{
		auto insertParagraph = std::make_unique<CInsertParagraphCommand>(paragraph, items, boost::none);
		REQUIRE(items.empty());
		insertParagraph->Execute();
		REQUIRE_FALSE(items.empty());
		insertParagraph->Unexecute();
		REQUIRE(items.empty());
	}

	SECTION("can not execute with wrong position")
	{
		auto insertParagraph = std::make_unique<CInsertParagraphCommand>(paragraph, items, 3);
		REQUIRE_THROWS(insertParagraph->Execute());
	}
}
