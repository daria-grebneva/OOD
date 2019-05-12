#include "stdafx.h"

#include "../composite/CEllipse.cpp"
#include "../composite/CEllipse.h"
#include "../composite/CFillStyle.cpp";
#include "../composite/CGroupFillStyle.cpp"
#include "../composite/CGroupLineStyle.cpp"
#include "../composite/CGroupShape.cpp";
#include "../composite/CGroupShape.h";
#include "../composite/CLineStyle.cpp";
#include "../composite/CRectangle.cpp"
#include "../composite/CRectangle.h"
#include "../composite/CShape.cpp";
#include "../composite/CShapes.cpp";
#include "../composite/CTriangle.cpp"
#include "../composite/CTriangle.h"

TEST_CASE("CGroupShape when created", "[CGroupShape]")
{
	auto groupShape = std::make_shared<CGroupShape>();
	SECTION("is empty")
	{
		REQUIRE(groupShape->GetShapesCount() == 0);
	}

	SECTION("has empty frame")
	{
		auto groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.left == 0);
		REQUIRE(groupFrame.top == 0);
		REQUIRE(groupFrame.width == 0);
		REQUIRE(groupFrame.height == 0);
	}

	SECTION("can set frame")
	{
		REQUIRE_NOTHROW(groupShape->SetFrame({ 50, 50, 100, 100 }));
	}

	SECTION("can set frame")
	{
		REQUIRE_NOTHROW(groupShape->SetFrame({ 50, 50, 100, 100 }));
	}

	SECTION("can not get style of empty group")
	{
		auto lineStyle = groupShape->GetLineStyle();
		REQUIRE(lineStyle->IsEnabled() == boost::none);
		auto fillStyle = groupShape->GetFillStyle();
		REQUIRE(lineStyle->IsEnabled() == boost::none);
	}

	SECTION("can not remove shape of empty group")
	{
		REQUIRE_THROWS(groupShape->RemoveShapeAtIndex(0));
	}
}
