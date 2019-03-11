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
		it->second(stream);
	}
	else
	{
		throw std::logic_error("Unknown command");
	}

	return std::unique_ptr<CShape>();
}

void CShapeFactory::ShowUsage(std::istream& args)
{
	std::cout << "To create a circle: " << CREATE_CIRCLE << "\n"
			  << "To create a ellipse: " << CREATE_ELLIPSE << "\n"
			  << "To create a rectangle: " << CREATE_RECTANGLE << "\n"
			  << "To create a triangle: " << CREATE_TRIANGLE << "\n"
			  << "To create a line: " << CREATE_LINE << "\n"
			  << "To get min shape perimeter: " << GET_MIN_PERIMETER << "\n"
			  << "To get max shape area: " << GET_MAX_AREA << "\n"
			  << "To draw shapes: " << DRAW << "\n"
			  << "To show usage: " << SHOW_USAGE << "\n";
}

void CShapeFactory::CheckIsEmptyShapesArray() const
{
	if (m_savedShapes.empty())
	{
		throw std::logic_error("Shapes array is empty");
	}
}

void CShapeFactory::DrawShapes(std::istream&)
{
	CheckIsEmptyShapesArray();
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color::White);
		for (auto& shape : m_savedShapes)
		{
			shape->Draw(canvas);
		}
		window.display();
	}
}

void CShapeFactory::GetMinPerimeterShape(std::istream& args) const
{
	CheckIsEmptyShapesArray();

	auto it = std::min_element(m_savedShapes.begin(), m_savedShapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) {
			return shape1->GetPerimeter() < shape2->GetPerimeter();
		});

	if (it != m_savedShapes.end())
	{
		std::cout << "MIN PERIMETER: " << std::endl;
		std::cout << (*it)->ToString() << std::endl;
	}
}

void CShapeFactory::GetMaxAreaShape(std::istream& args) const
{
	CheckIsEmptyShapesArray();

	auto it = std::max_element(m_savedShapes.begin(), m_savedShapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) {
			return shape1->GetArea() < shape2->GetArea();
		});
	if (it != m_savedShapes.end())
	{
		std::cout << "MAX AREA: " << std::endl;
		std::cout << (*it)->ToString() << std::endl;
	}
}

void CShapeFactory::CreateCircle(std::istream& args)
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

		auto circlePtr = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
		m_savedShapes.push_back(std::move(circlePtr));
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for cicle creating");
	}
}

void CShapeFactory::CreateEllipse(std::istream& args)
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

		auto ellipsePtr = std::make_shared<CEllipse>(center, horizontalRadius, verticalRadius, outlineColor, fillColor);
		m_savedShapes.push_back(std::move(ellipsePtr));
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for ellipse creating");
	}
}

void CShapeFactory::CreateLine(std::istream& args)
{
	Color outlineColor;
	CPoint start;
	CPoint end;

	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{

		auto linePtr = std::make_shared<CLineSegment>(start, end, outlineColor);
		m_savedShapes.push_back(std::move(linePtr));
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for line creating");
	}
}

void CShapeFactory::CreateRectangle(std::istream& args)
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

		auto rectanglePtr = std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
		m_savedShapes.push_back(std::move(rectanglePtr));
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for rectangle creating");
	}
}

void CShapeFactory::CreateTriangle(std::istream& args)
{
	Color fillColor;
	Color outlineColor;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;

	if (args >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> outlineColor >> fillColor)
	{
		auto trianglePtr = std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
		m_savedShapes.push_back(std::move(trianglePtr));
	}
	else
	{
		throw std::invalid_argument("Incorrect argument for triangle creating");
	}
}
