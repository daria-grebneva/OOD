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
	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;

	std::unique_ptr<CCircle> CreateCircle(std::istream& args);
	std::unique_ptr<CLineSegment> CreateLine(std::istream& args);
	std::unique_ptr<CRectangle> CreateRectangle(std::istream& args);
	std::unique_ptr<CTriangle> CreateTriangle(std::istream& args);
	std::unique_ptr<CEllipse> CreateEllipse(std::istream& args);

	const ActionMap m_action = { { CREATE_CIRCLE, bind(&CShapeFactory::CreateCircle, this, std::placeholders::_1) },
		{ CREATE_RECTANGLE, bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1) },
		{ CREATE_TRIANGLE, bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1) },
		{ CREATE_LINE, bind(&CShapeFactory::CreateLine, this, std::placeholders::_1) },
		{ CREATE_ELLIPSE, bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1) } };
};
