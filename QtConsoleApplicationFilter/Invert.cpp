#include "Invert.h"
#include <iostream>

Invert::Invert()
{
	width = 1;
	height = 1;

	conv2d = new double* [height];

	conv2d[0] = new double[width] {1};
}

unsigned char Invert::execute(const Image* image, int x, int y, Channel channel, ImagePointRule rule)
{
	QColor c = image->pixel(x, y, rule);
	double res = 255 - color_in_channel(c, channel);

	return res;
}