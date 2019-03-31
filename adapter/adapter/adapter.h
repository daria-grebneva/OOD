#pragma once
#include "stdafx.h"

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib
{
	// ����� ��� ���������
	class ICanvas
	{
	public:
		// ������ "����" � ����� x, y
		virtual void MoveTo(int x, int y) = 0;
		// ������ ����� � ������� �������, ���������� ���� � ����� x,y 
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// ���������� ������ ��� ���������
	class CCanvas : public ICanvas
	{
	public:
		void MoveTo(int x, int y) override
		{
			std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
		}
		void LineTo(int x, int y) override
		{
			std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
		}
	};
}

// ������������ ���� ���������� ��� ��������� ����� (���������� graphics_lib)
// ��� ���������� ���������� ��� ���������
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// ��������� ��������, ������� ����� ���� ���������� �� ������ �� graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point & p1, const Point & p2, const Point & p3)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.MoveTo(m_p1.x, m_p1.y);

			canvas.LineTo(m_p2.x, m_p2.y);
			canvas.LineTo(m_p3.x, m_p3.y);
			canvas.LineTo(m_p1.x, m_p1.y);
		}

	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point & leftTop, int width, int height)
			: m_leftTop(leftTop)
			, m_width(width)
			, m_height(height)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.MoveTo(m_leftTop.x, m_leftTop.y);

			canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}
	private:
		Point m_leftTop;
		int m_width;
		int m_height;
	};

	// ��������, ��������� �������� ICanvasDrawable-������� �� ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas & canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable & drawable)
		{
			drawable.Draw(m_canvas);
		}
	private:
		graphics_lib::ICanvas& m_canvas;
	};
}

// ������������ ���� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // ��������� ���������, ���� ��� ���� ������
			{
				EndDraw();
			}
		}

		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// ��������� ��������� �����
		void DrawLine(const CPoint & start, const CPoint & end)
		{
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
				% start.x % start.y % end.x % end.y << std::endl;
		}

		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}
	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}

// ������������ ���� ���������� (�������� ��� �����������)
namespace app
{
	class CModernRendererAdapter : public graphics_lib::ICanvas
	{
	public:
		CModernRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& render)
			: m_render(render)
			, m_point(0, 0)
		{
			m_render.BeginDraw();
		}

		void MoveTo(int x, int y) override
		{
			m_point = modern_graphics_lib::CPoint(x, y);
		}

		void LineTo(int x, int y) override
		{
			m_render.DrawLine(m_point, modern_graphics_lib::CPoint(x, y));
			MoveTo(x, y);
		}

	private:
		modern_graphics_lib::CPoint m_point;
		modern_graphics_lib::CModernGraphicsRenderer& m_render;

	};

	void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		CRectangle rectangle({ 30, 40 }, 18, 24);

		// TODO: ���������� ������������� � ����������� ��� ������ painter
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
		//(void)&renderer; // ��������� �������������� � �������������� ����������

		// TODO: ��� ������ ������������ ������� PaintPicture() ����������
		// ������� �� renderer
		// ���������: ����������� ������� "�������"

		CModernRendererAdapter adapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(adapter);

		PaintPicture(painter);
	}
}

namespace graphics_lib_pro
{
	// ����� ��� ���������
	class ICanvas
	{
	public:
		// ��������� ����� � ������� 0xRRGGBB
		virtual void SetColor(uint32_t rgbColor) = 0;
		virtual void MoveTo(int x, int y) = 0;
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// ���������� ������ ��� ���������
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override
		{
			// TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
		}
		void MoveTo(int x, int y) override
		{
			// ���������� �������� ��� ���������
		}
		void LineTo(int x, int y) override
		{
			// ���������� �������� ��� ���������
		}
	};
}

// ������������ ���� ����������� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			// ���������� �������� ��� ���������
		}

		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw()
		{
			// ���������� �������� ��� ���������
		}

		// ��������� ��������� �����
		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
		{
			// TODO: ������� � output ���������� ��� ��������� ����� � ����
			// <line fromX="3" fromY="5" toX="5" toY="17">
			//   <color r="0.35" g="0.47" b="1.0" a="1.0" />
			// </line>
			// ����� �������� ������ ����� BeginDraw() � EndDraw()
		}

		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw()
		{
			// ���������� �������� ��� ���������
		}
	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}
