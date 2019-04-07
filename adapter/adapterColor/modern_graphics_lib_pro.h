#pragma once
#include <iostream>
#include <sstream>
#include <boost/format.hpp>

// ������������ ���� ����������� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y)
			: x(x)
			, y(y)
		{
		}

		int x;
		int y;
	};

	// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
		}
		float r, g, b, a;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm)
			: m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			// ���������� �������� ��� ���������
			if (m_drawing) // ��������� ���������, ���� ��� ���� ������
			{
				EndDraw();
			}
		}

		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw()
		{
			// ���������� �������� ��� ���������
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// ��������� ��������� �����
		void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
		{
			// TODO: ������� � output ���������� ��� ��������� ����� � ����
			// <line fromX="3" fromY="5" toX="5" toY="17">
			//   <color r="0.35" g="0.47" b="1.0" a="1.0" />
			// </line>
			// ����� �������� ������ ����� BeginDraw() � EndDraw()
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
				% start.x % start.y % end.x % end.y
				<< std::endl
				<< boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%"/>)")
				% color.r % color.g % color.b % color.a
				<< std::endl
				<< "  </line>"
				<< std::endl;
		}

		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw()
		{
			// ���������� �������� ��� ���������
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}

	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
} // namespace modern_graphics_lib_pro
