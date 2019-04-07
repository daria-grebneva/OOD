#pragma once
#include "stdafx.h"
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
class CModernRendererAdapter : public graphics_lib::ICanvas,
	private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CModernRendererAdapter(std::ostream& strm)
		: modern_graphics_lib::CModernGraphicsRenderer(strm)
		, m_point(0, 0)
	{
		BeginDraw();
	}

	~CModernRendererAdapter()
	{
		EndDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_point = modern_graphics_lib::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		DrawLine(m_point, modern_graphics_lib::CPoint(x, y));
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CPoint m_point;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	// TODO: нарисовать прямоугольник и треугольник при помощи painter
	painter.Draw(rectangle);
	painter.Draw(triangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
	//(void)&renderer; // устраняем предупреждение о неиспользуемой переменной

	// TODO: при помощи существующей функции PaintPicture() нарисовать
	// картину на renderer
	// Подсказка: используйте паттерн "Адаптер"

	CModernRendererAdapter adapter(std::cout);

	shape_drawing_lib::CCanvasPainter painter(adapter);

	PaintPicture(painter);
}
} // namespace app
