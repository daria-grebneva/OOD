#include "stdafx.h"
#include "CShapeFactory.h"
#include "CCanvas.h"

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream stream(description);

	std::string action;
	stream >> action;

	auto it = m_action.find(action);
	if (it != m_action.end())
	{
		return it->second(stream);
	}
	else
	{
		throw std::logic_error("Unknown command");
	}

	return std::unique_ptr<CShape>();
}

std::unique_ptr<CCircle> CShapeFactory::CreateCircle(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint center;
	double radius;

	if (args >> center.x >> center.y >> radius >> outlineColor >> fillColor)
	{

		if (radius < 0)
		{
			throw std::invalid_argument("Radius less than 0");
		}

		return std::make_unique<CCircle>(center, radius, outlineColor, fillColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for circle creating");
	}
}

std::unique_ptr<CLineSegment> CShapeFactory::CreateLine(std::istream& args)
{
	Color outlineColor;
	CPoint start;
	CPoint end;

	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{

		return std::make_unique<CLineSegment>(start, end, outlineColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for line creating");
	}
}

std::unique_ptr<CEllipse> CShapeFactory::CreateEllipse(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint center;
	double horizontalRadius;
	double verticalRadius;

	if (args >> center.x >> center.y >> horizontalRadius >> verticalRadius >> outlineColor >> fillColor)
	{

		if (horizontalRadius < 0 || verticalRadius < 0)
		{
			throw std::invalid_argument("Radius less than 0");
		}

		return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, outlineColor, fillColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for ellipse creating");
	}
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint center;
	float radius;
	size_t vertexCount;

	if (args >> center.x >> center.y >> radius >> vertexCount >> outlineColor >> fillColor)
	{

		return std::make_unique<CRegularPolygon>(center, radius, vertexCount, outlineColor, fillColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for regular polygon creating");
	}
}

std::unique_ptr<CRectangle> CShapeFactory::CreateRectangle(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint leftTop;
	double width;
	double height;

	if (args >> leftTop.x >> leftTop.y >> width >> height >> outlineColor >> fillColor)
	{
		if (width < 0)
		{
			throw std::invalid_argument("Width less than 0");
		}

		if (height < 0)
		{
			throw std::invalid_argument("Height less than 0");
		}

		return std::make_unique<CRectangle>(leftTop, width, height, outlineColor, fillColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for rectangle creating");
	}
}

std::unique_ptr<CTriangle> CShapeFactory::CreateTriangle(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;

	if (args >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> outlineColor >> fillColor)
	{
		return std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for triangle creating");
	}
}
