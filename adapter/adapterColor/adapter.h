#pragma once
#include "stdafx.h"
#include "graphics_lib_pro.h"
#include "modern_graphics_lib_pro.h"
#include "shape_drawing_lib.h"

// ������������ ���� ���������� (�������� ��� �����������)
namespace app
{
class CModernRendererAdapter : public graphics_lib_pro::ICanvas,
	private modern_graphics_lib_pro::CModernGraphicsRenderer
{
public:
	CModernRendererAdapter(std::ostream& strm)
		: modern_graphics_lib_pro::CModernGraphicsRenderer(strm)
		, m_point(0, 0)
		, m_rgbColor(0, 0, 0, 0)
	{
		BeginDraw();
	}

	~CModernRendererAdapter()
	{
		EndDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_point = modern_graphics_lib_pro::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		DrawLine(m_point, modern_graphics_lib_pro::CPoint(x, y), m_rgbColor);
		MoveTo(x, y);
	}

	void SetColor(uint32_t rgbColor) override
	{
		m_rgbColor.r = ((rgbColor >> 16) & 0xFF) / 255.f;
		m_rgbColor.g = ((rgbColor >> 8) & 0xFF) / 255.f;
		m_rgbColor.b = (rgbColor & 0xFF) / 255.f;
		m_rgbColor.a = 1.0;
	}

private:
	modern_graphics_lib_pro::CPoint m_point;
	modern_graphics_lib_pro::CRGBAColor m_rgbColor;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xFFFFFF);
	CRectangle rectangle({ 30, 40 }, 18, 24, 0xFFFFFF);

	// TODO: ���������� ������������� � ����������� ��� ������ painter
	painter.Draw(rectangle);
	painter.Draw(triangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib_pro::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(std::cout);
	//(void)&renderer; // ��������� �������������� � �������������� ����������

	// TODO: ��� ������ ������������ ������� PaintPicture() ����������
	// ������� �� renderer
	// ���������: ����������� ������� "�������"

	CModernRendererAdapter adapter(std::cout);

	shape_drawing_lib::CCanvasPainter painter(adapter);

	PaintPicture(painter);
}
} // namespace app
