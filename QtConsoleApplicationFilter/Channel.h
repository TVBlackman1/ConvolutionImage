#pragma once

#include "qcolor.h"
#include <iostream>

enum class Channel
{
	Red,
	Green,
	Blue,
	BlackAndWhite
};

inline unsigned char color_in_channel(QColor color, Channel channel)
{
	switch (channel)
	{
	case Channel::Red:
		return color.red();
	case Channel::Green:
		return color.green();
	case Channel::Blue:
		return color.blue();
	default:
	case Channel::BlackAndWhite:
		//std::cout << color.red() << "," << color.green() << "," << color.blue() << " => " << (color.red() + color.green() + color.blue()) / 3 << std::endl;
		return (color.red() + color.green() + color.blue()) / 3;
	}
}

inline QColor char_to_color_in_channel(unsigned char value, Channel channel)
{
	switch (channel)
	{
	case Channel::Red:
		return QColor(value, 0, 0);
	case Channel::Green:
		return QColor(0, value, 0);
	case Channel::Blue:
		return QColor(0, 0, value);
	default:
	case Channel::BlackAndWhite:
		return QColor(value, value, value);
	}
}

inline QColor color_sum(QColor c1, QColor c2)
{
	QColor ret(c1);

	int red = c1.red() + c2.red();
	if (red > 255) red = 255;

	int green = c1.green() + c2.green();
	if (green > 255) green = 255;

	int blue = c1.blue() + c2.blue();
	if (blue > 255) blue = 255;
	ret.setRgb(red, green, blue);

	return ret;
}