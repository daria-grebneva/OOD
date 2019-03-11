#include "stdafx.h"
#include "CUtils.h"

const uint32_t CUtils::ColorToHex(const Color& str)
{
	uint32_t x;
	std::stringstream ss;
	std::string color = "";

	switch (str)
	{
	case (Color::BLACK):
		color = "000000ff";
		break;
	case (Color::PEACH):
		color = "ff877cff";
		break;
	case (Color::BROWN):
		color = "331b18ff";
		break;
	case (Color::LIGHT_BROWN):
		color = "4c2825ff";
		break;
	case (Color::LIGHT_BLUE):
		color = "c6e5e5ff";
		break;
	default:
		break;
	}
	ss << std::hex << color;
	ss >> x;
	return x;
}
