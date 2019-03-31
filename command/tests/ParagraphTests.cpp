#include "stdafx.h"
#include "../command/History.h"
#include "../command/Paragraph.h"

TEST_CASE("CParagraph", "[CParagraph]")
{
	CHistory history;
	std::string text = "<!-- the title -->";
	CParagraph paragraph(history, text);

	SECTION("create paragraph and get text")
	{
		REQUIRE(paragraph.GetText() == text);
	}

	SECTION("check set text")
	{
		std::string text = "new text for paragraph";
		paragraph.SetText(text);
		REQUIRE(paragraph.GetText() == text);
	}
}
