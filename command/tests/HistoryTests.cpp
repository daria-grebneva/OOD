#include "stdafx.h"
#include "../command/History.h"
#include "../command/InsertParagraphCommand.h"
#include "../command/Paragraph.h"

TEST_CASE("CHistory", "[CHistory]")
{
	CHistory history;
	std::string text = "<!-- the title -->";
	auto paragraph = std::make_shared<CParagraph>(history, text);
	std::vector<CDocumentItem> items;

	SECTION("check add and execute command")
	{
		history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(paragraph, items, 0));
		REQUIRE_FALSE(items.empty());
	}

	SECTION("can undo")
	{
		history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(paragraph, items, 0));
		REQUIRE_FALSE(items.empty());
		REQUIRE(history.CanUndo());
		history.Undo();
		REQUIRE(items.empty());
	}

	SECTION("can redo")
	{
		history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(paragraph, items, 0));
		REQUIRE_FALSE(items.empty());
		REQUIRE(history.CanUndo());
		history.Undo();
		REQUIRE(items.empty());
		REQUIRE(history.CanRedo());
		history.Redo();
		REQUIRE_FALSE(items.empty());
	}

	SECTION("check limited size")
	{
		std::string target;
		for (size_t i = 0; i < 15; ++i)
		{
			history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(paragraph, items, i));
		}
		size_t size = 0;
		size_t expectedSize = 10;

		while (history.CanUndo())
		{
			history.Undo();
			++size;
		}

		REQUIRE(size == expectedSize);
	}

	SECTION("can not undo when clear")
	{
		REQUIRE_FALSE(history.CanUndo());
	}

	SECTION("can not redo when clear")
	{
		REQUIRE_FALSE(history.CanRedo());
	}
}
