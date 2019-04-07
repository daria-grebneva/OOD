#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);

	void SetLineColor(RGBAColor color) override;
	void SetLineThickness(float thickness) override;
	void SetFillColor(RGBAColor const& color) override;
	/*void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;*/

	void DrawEllipse(double left, double top, double width, double height) override;
	void DrawTriangle(PointD const& p1, PointD const& p2, PointD const& p3) override;
	void DrawRectangle(PointD const& leftTop, double width, double height) override;
private:
	void DrawLine(const PointD& startPoint, const PointD& endPoint) override;
	void FillPolygon(const std::vector<PointD>& vertices);
	/*void FillShape(std::vector<PointD> const& points) override;
	void LineShape(std::vector<PointD> const& points) override;*/

	float m_lineThickness;
	RGBAColor m_lineColor;
	RGBAColor m_fillColor;
	sf::RenderWindow& m_window;
};