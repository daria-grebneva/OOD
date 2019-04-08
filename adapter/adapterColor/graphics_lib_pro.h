#pragma once
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace graphics_lib_pro
{
// Холст для рисования
class ICanvas
{
public:
	// Установка цвета в формате 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		// TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
		std::stringstream strstm;
		strstm << std::hex << rgbColor;
		std::string str;
		strstm >> str;
		const std::string upper_str = boost::algorithm::to_upper_copy(str);
		std::cout << "SetColor #" << upper_str << std::endl;
	}
	void MoveTo(int x, int y) override
	{
		// Реализация остается без изменения
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		// Реализация остается без изменения
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
} // namespace graphics_lib_pro
