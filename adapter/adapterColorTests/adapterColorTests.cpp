#include "stdafx.h"
#include "../adapterColor/adapter.h"

TEST_CASE("CModernRendererAdapter", "[CModernRendererAdapter]")
{
	SECTION("check setting color")
	{
		std::stringstream strstm;

		{
			app::CModernRendererAdapter adapter(strstm);
			adapter.SetColor(0xFFFFFF);

			adapter.MoveTo(5, 15);
			adapter.LineTo(10, 30);
		}

		REQUIRE(strstm.str() == "<draw>\n  <line fromX=\"5\" fromY=\"15\" toX=\"10\" toY=\"30\"/>\n    <color r=\"1\" g=\"1\" b=\"1\" a=\"1\"/>\n  </line>\n</draw>\n");
	}

	SECTION("check move to point")
	{
		std::stringstream strstm;
		app::CModernRendererAdapter adapter(strstm);

		adapter.MoveTo(5, 15);
		REQUIRE(strstm.str() == "<draw>\n");
	}

	SECTION("check line to point with default color")
	{
		std::stringstream strstm;

		{
			app::CModernRendererAdapter adapter(strstm);

			adapter.MoveTo(5, 15);
			adapter.LineTo(10, 30);
		}

		REQUIRE(strstm.str() == "<draw>\n  <line fromX=\"5\" fromY=\"15\" toX=\"10\" toY=\"30\"/>\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\"/>\n  </line>\n</draw>\n");
	}
}