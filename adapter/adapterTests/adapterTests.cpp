#include "stdafx.h"
#include "../adapter/adapter.h"

TEST_CASE("CModernRendererAdapter", "[CModernRendererAdapter]")
{
	SECTION("check move to point")
	{
		std::stringstream strstm;
		modern_graphics_lib::CModernGraphicsRenderer renderer(strstm);
		app::CModernRendererAdapter adapter(renderer);

		adapter.MoveTo(5, 15);

		REQUIRE(strstm.str() == "<draw>\n");
	}

	SECTION("check line to point")
	{
		std::stringstream strstm;
		modern_graphics_lib::CModernGraphicsRenderer renderer(strstm);
		app::CModernRendererAdapter adapter(renderer);

		adapter.MoveTo(5, 15);
		adapter.LineTo(10, 30);

		REQUIRE(strstm.str() == "<draw>\n  <line fromX=\"5\" fromY=\"15\" toX=\"10\" toY=\"30\"/>\n");
	}
}
