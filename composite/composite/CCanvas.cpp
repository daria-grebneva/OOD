#include "stdafx.h"
#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
}

void CCanvas::SetLineThickness(float thickness)
{
	m_lineThickness = thickness;
}

void CCanvas::SetFillColor(RGBAColor const& color)
{
	m_fillColor = color;
}

void CCanvas::DrawLine(const PointD& startPoint, const PointD& endPoint)
{
	sf::Vertex vertices[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(startPoint.x), static_cast<float>(startPoint.y)),
		sf::Color(sf::Uint32(m_lineColor))),

		sf::Vertex(sf::Vector2f(static_cast<float>(endPoint.x), static_cast<float>(endPoint.y)),
		sf::Color(sf::Uint32(m_lineColor)))
	};
	m_window.draw(vertices, static_cast<size_t>(m_lineThickness), sf::Lines);
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto horizontalRadius = static_cast<float>(width / 2.f);
	auto verticalRadius = static_cast<float>(height / 2.f);

	sf::CircleShape ellipse(horizontalRadius);
	ellipse.setPosition(static_cast<float>(left), static_cast<float>(top));
	ellipse.setOutlineColor(sf::Color(sf::Uint32(m_lineColor)));
	ellipse.setFillColor(sf::Color(sf::Uint32(m_fillColor)));
	ellipse.setOutlineThickness(m_lineThickness);
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	m_window.draw(ellipse);
}

void CCanvas::DrawTriangle(PointD const& p1, PointD const& p2, PointD const& p3)
{
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p1, p3);
	FillPolygon({p1 , p2, p3});
}

void CCanvas::DrawRectangle(PointD const& leftTop, double width, double height)
{
	std::vector<PointD> points = {
		leftTop,
		{ leftTop.x + width, leftTop.y },
		{ leftTop.x + width, leftTop.y + height },
		{ leftTop.x, leftTop.y + height },
	};

	FillPolygon(points);

	DrawLine(leftTop, { leftTop.x + width, leftTop.y });
	DrawLine({ leftTop.x + width, leftTop.y }, { leftTop.x + width, leftTop.y + height });
	DrawLine({ leftTop.x + width, leftTop.y + height }, { leftTop.x, leftTop.y + height });
	DrawLine({ leftTop.x, leftTop.y + height }, leftTop);
}

void CCanvas::FillPolygon(const std::vector<PointD>& vertices)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertices.size());
	polygon.setFillColor(sf::Color(sf::Uint32(m_fillColor)));

	for (size_t i = 0; i < vertices.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(vertices[i].x), static_cast<float>(vertices[i].y)));
	}
	m_window.draw(polygon);
}