#pragma once
#include <iostream>
#include <map>
#include <sstream>

enum class Color
{
	BLACK,
	PEACH,
	BROWN,
	LIGHT_BROWN,
	LIGHT_BLUE,
};

const std::map<std::string, Color> STR_TO_COLOR = {
	{ "black", Color::BLACK },
	{ "peach", Color::PEACH },
	{ "brown", Color::BROWN },
	{ "light-brown", Color::LIGHT_BROWN },
	{ "light-blue", Color::LIGHT_BLUE },
};

const std::map<Color, std::string> COLOR_TO_STR = {
	{ Color::BLACK, "black" },
	{ Color::PEACH, "peach" },
	{ Color::BROWN, "brown" },
	{ Color::LIGHT_BROWN, "light-brown" },
	{ Color::LIGHT_BLUE, "light-blue" },
};

inline std::istream& operator>>(std::istream& str, Color& color)
{
	std::string value;
	if (str >> value)
	{
		auto result = STR_TO_COLOR.find(value);
		if (result == STR_TO_COLOR.end())
		{
			std::cout << value << std::endl;
			throw std::invalid_argument("invalid color name");
		}

		color = result->second;
	}

	return str;
}

inline std::ostream& operator<<(std::ostream& str, const Color& value)
{
	std::string color = "";

	auto result = COLOR_TO_STR.find(value);
	if (result != COLOR_TO_STR.end())
	{
		color = result->second;
	}

	str << color;

	return str;
}
