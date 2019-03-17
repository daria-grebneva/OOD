#include "stdafx.h"
#include "CCanvas.h"
#include "Config.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor)
{
	sf::Vertex vertices[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(startPoint.x), static_cast<float>(startPoint.y)),
			sf::Color(sf::Uint32(lineColor))),

		sf::Vertex(sf::Vector2f(static_cast<float>(endPoint.x), static_cast<float>(endPoint.y)),
			sf::Color(sf::Uint32(lineColor)))
	};
	m_window.draw(vertices, static_cast<size_t>(THICKNESS), sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& vertices, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertices.size());
	polygon.setFillColor(sf::Color(sf::Uint32(fillColor)));

	for (size_t i = 0; i < vertices.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(vertices[i].x), static_cast<float>(vertices[i].y)));
	}
	m_window.draw(polygon);
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));

	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(THICKNESS);
	circle.setOutlineColor(sf::Color(sf::Uint32(lineColor)));
	m_window.draw(circle);
}

void CCanvas::DrawEllipse(double left, double top, double width, double height, uint32_t lineColor)
{
	auto horizontalRadius = static_cast<float>(width / 2.f);
	auto verticalRadius = static_cast<float>(height / 2.f);

	sf::CircleShape ellipse(horizontalRadius);
	ellipse.setPosition(static_cast<float>(left), static_cast<float>(top));
	ellipse.setOutlineColor(sf::Color(sf::Uint32(lineColor)));
	ellipse.setOutlineThickness(THICKNESS);
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	m_window.draw(ellipse);
}

void CCanvas::FillCircle(const CPoint& center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));

	circle.setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));
	circle.setFillColor(sf::Color(sf::Uint32(fillColor)));
	m_window.draw(circle);
}

void CCanvas::FillEllipse(double left, double top, double width, double height, uint32_t fillColor)
{
	auto horizontalRadius = static_cast<float>(width / 2.f);
	auto verticalRadius = static_cast<float>(height / 2.f);
	sf::CircleShape ellipse(horizontalRadius);

	ellipse.setPosition(left, top);
	ellipse.setFillColor(sf::Color(sf::Uint32(fillColor)));
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	m_window.draw(ellipse);
}
