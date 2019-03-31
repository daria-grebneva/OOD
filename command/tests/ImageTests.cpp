#include "stdafx.h"
#include "../command/History.h"
#include "../command/Image.h"
#include "Constants.h"

TEST_CASE("CImage", "[CImage]")
{
	CHistory history;
	CImage img(history, IMAGE_PATH, 100, 150);

	SECTION("check image path")
	{
		REQUIRE(img.GetPath().string() == IMAGE_PATH);
	}

	SECTION("check image width")
	{
		REQUIRE(img.GetWidth() == 100);
	}

	SECTION("check image height")
	{
		REQUIRE(img.GetHeight() == 150);
	}

	SECTION("check image resize")
	{
		img.Resize(300, 600);
		REQUIRE(img.GetWidth() == 300);
		REQUIRE(img.GetHeight() == 600);
	}

	SECTION("can not create image with wrong path")
	{
		REQUIRE_THROWS(CImage(history, "E:/gdgdg.jpg", 100, 150));
	}

	SECTION("can not create image with wrong extension")
	{
		std::string path = boost::filesystem::change_extension(IMAGE_PATH, ".doc").string();
		REQUIRE_THROWS(CImage(history, path, 100, 150));
	}
}
