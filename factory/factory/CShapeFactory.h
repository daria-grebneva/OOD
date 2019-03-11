#pragma once
#include "CCircle.h"
#include "CEllipse.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "Config.h"
#include "IShape.h"
#include "IShapeFactory.h"

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string& description) override;

private:
	typedef std::map<std::string, std::function<void(std::istream& args)>> Action;

	std::vector<std::shared_ptr<IShape>> m_savedShapes;

	void DrawShapes(std::istream& args);
	void CreateCircle(std::istream& args);
	void CreateLine(std::istream& args);
	void CreateRectangle(std::istream& args);
	void CreateTriangle(std::istream& args);
	void CreateEllipse(std::istream& args);
	void GetMinPerimeterShape(std::istream& args) const;
	void GetMaxAreaShape(std::istream& args) const;
	void ShowUsage(std::istream& args);
	void CheckIsEmptyShapesArray() const;

	const Action m_action = { { CREATE_CIRCLE, bind(&CShapeFactory::CreateCircle, this, std::placeholders::_1) },
		{ CREATE_RECTANGLE, bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1) },
		{ CREATE_TRIANGLE, bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1) },
		{ CREATE_LINE, bind(&CShapeFactory::CreateLine, this, std::placeholders::_1) },
		{ CREATE_ELLIPSE, bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1) },
		{ GET_MIN_PERIMETER, bind(&CShapeFactory::GetMinPerimeterShape, this, std::placeholders::_1) },
		{ GET_MAX_AREA, bind(&CShapeFactory::GetMaxAreaShape, this, std::placeholders::_1) },
		{ DRAW, bind(&CShapeFactory::DrawShapes, this, std::placeholders::_1) },
		{ SHOW_USAGE, bind(&CShapeFactory::ShowUsage, this, std::placeholders::_1) } };
};
