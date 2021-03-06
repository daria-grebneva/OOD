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
#include "../composite/CUtils.h"

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

	SECTION("can not change frame")
	{
		REQUIRE_NOTHROW(groupShape->SetFrame({ 50, 50, 100, 100 }));
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

	SECTION("can insert a shape")
	{
		auto rectangle = std::make_shared<CRectangle>(PointD{ 10, 10 }, 10, 10);
		groupShape->InsertShape(rectangle, 0);
		REQUIRE(groupShape->GetShapesCount() == 1);
	}
}

TEST_CASE("CGroupShape with shapes", "[CGroupShape]")
{
	auto groupShape = std::make_shared<CGroupShape>();

	auto rectangle = std::make_shared<CRectangle>(PointD{ 10, 10 }, 300, 100);
	auto rectFillStyle = rectangle->GetFillStyle();
	auto rectLineStyle = rectangle->GetLineStyle();

	auto triangle = std::make_shared<CTriangle>(PointD{ 20, 20 }, PointD{ 30, 30 }, PointD{ 50, 50 });
	auto triangleFillStyle = triangle->GetFillStyle();
	auto triangleLineStyle = triangle->GetLineStyle();

	SECTION("with common style return their common style")
	{
		rectFillStyle->SetColor(Colors::YELLOW);
		triangleFillStyle->SetColor(Colors::YELLOW);

		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		std::shared_ptr<const IStyle> commonStyle = groupShape->GetFillStyle();

		REQUIRE(commonStyle->IsEnabled() == true);
		REQUIRE(commonStyle->GetColor() == Colors::YELLOW);
	}

	SECTION("with different style return none")
	{
		rectFillStyle->SetColor(Colors::YELLOW);
		triangleFillStyle->SetColor(Colors::BROWN);

		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		std::shared_ptr<const IStyle> commonStyle = groupShape->GetFillStyle();

		REQUIRE(commonStyle->GetColor() == boost::none);
	}

	SECTION("can change group fill style")
	{
		rectFillStyle->SetColor(Colors::YELLOW);
		triangleFillStyle->SetColor(Colors::BROWN);

		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		std::shared_ptr<const IStyle> commonStyle = groupShape->GetFillStyle();

		REQUIRE(commonStyle->GetColor() == boost::none);
		groupShape->GetFillStyle()->SetColor(Colors::YELLOW);
		REQUIRE(commonStyle->GetColor() == Colors::YELLOW);
	}

	SECTION("can change group line style")
	{
		rectLineStyle->SetColor(Colors::YELLOW);
		triangleLineStyle->SetColor(Colors::BROWN);

		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		std::shared_ptr<const IStyle> commonStyle = groupShape->GetLineStyle();

		REQUIRE(commonStyle->GetColor() == boost::none);
		groupShape->GetLineStyle()->SetColor(Colors::YELLOW);
		REQUIRE(commonStyle->GetColor() == Colors::YELLOW);
	}

	SECTION("can change group line thickness")
	{
		rectLineStyle->SetLineThickness(2);
		triangleLineStyle->SetLineThickness(4);

		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		auto commonStyle = groupShape->GetLineStyle();

		REQUIRE(commonStyle->GetLineThickness() == boost::none);
		groupShape->GetLineStyle()->SetLineThickness(3);
		REQUIRE(commonStyle->GetLineThickness() == 3.f);
	}

	SECTION("empty after removing shape")
	{
		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 1);
		REQUIRE(groupShape->GetShapesCount() == 2);
		groupShape->RemoveShapeAtIndex(1);

		REQUIRE(groupShape->GetShapesCount() == 1);
	}

	SECTION("get right shapes count")
	{
		groupShape->InsertShape(rectangle, 0);
		groupShape->InsertShape(triangle, 0);
		REQUIRE(groupShape->GetShapesCount() == 2);
	}

	SECTION("frame of group is inner shape frame")
	{
		auto rectFrame = rectangle->GetFrame();
		groupShape->InsertShape(rectangle, 0);

		auto groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.top == rectFrame.top);
		REQUIRE(groupFrame.left == rectFrame.left);
		REQUIRE(groupFrame.height == rectFrame.height);
		REQUIRE(groupFrame.width == rectFrame.width);
	}

	SECTION("change frame after adding shape")
	{
		auto triangleFrame = triangle->GetFrame();
		groupShape->InsertShape(triangle, 0);

		auto groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.top == triangleFrame.top);
		REQUIRE(groupFrame.left == triangleFrame.left);
		REQUIRE(groupFrame.height == triangleFrame.height);
		REQUIRE(groupFrame.width == triangleFrame.width);

		auto rectFrame = rectangle->GetFrame();
		groupShape->InsertShape(rectangle, 1);

		groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.top == rectFrame.top);
		REQUIRE(groupFrame.left == rectFrame.left);
		REQUIRE(groupFrame.height == rectFrame.height);
		REQUIRE(groupFrame.width == rectFrame.width);
	}

	SECTION("change frame after changing its own frame")
	{
		auto rectFrame = rectangle->GetFrame();
		groupShape->InsertShape(rectangle, 0);

		auto groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.top == rectFrame.top);
		REQUIRE(groupFrame.left == rectFrame.left);
		REQUIRE(groupFrame.height == rectFrame.height);
		REQUIRE(groupFrame.width == rectFrame.width);

		RectD newFrame = { 5, 5, 400, 800 };
		groupShape->SetFrame(newFrame);

		groupFrame = groupShape->GetFrame();
		REQUIRE(groupFrame.top == newFrame.top);
		REQUIRE(groupFrame.left == newFrame.left);
		REQUIRE(groupFrame.height == newFrame.height);
		REQUIRE(groupFrame.width == newFrame.width);
	}

	SECTION("empty group doesn't change parent group frame")
	{
		auto picture = std::make_shared<CGroupShape>();
		auto pictureNull = std::make_shared<CGroupShape>();

		auto nullRect = std::make_shared<CRectangle>(PointD{ 0, 0 }, 0, 0);
		nullRect->GetFillStyle()->SetColor(Colors::BROWN);
		nullRect->GetLineStyle()->SetColor(Colors::BLACK);
		auto earth = std::make_shared<CRectangle>(PointD{ 10, 10 }, 700, 320);
		earth->GetFillStyle()->SetColor(Colors::BROWN);
		earth->GetLineStyle()->SetColor(Colors::BLACK);

		pictureNull->InsertShape(nullRect, 0);
		picture->InsertShape(earth, 0);

		auto pictureFrame = picture->GetFrame();
		auto earthFrame = earth->GetFrame();
		REQUIRE(pictureFrame.top == earthFrame.top);
		REQUIRE(pictureFrame.left == earthFrame.left);
		REQUIRE(pictureFrame.height == earthFrame.height);
		REQUIRE(pictureFrame.width == earthFrame.width);
		picture->InsertShape(pictureNull, 1);

		pictureFrame = picture->GetFrame();
		REQUIRE(pictureFrame.top == earthFrame.top);
		REQUIRE(pictureFrame.left == earthFrame.left);
		REQUIRE(pictureFrame.height == earthFrame.height);
		REQUIRE(pictureFrame.width == earthFrame.width);
	}
}
