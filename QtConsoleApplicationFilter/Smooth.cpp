#include "Smooth.h"
#include <iostream>

Smooth::Smooth()
{
	width = 5;
	height = 5;

	conv2d = new double* [height];

	conv2d[0] = new double[width] {1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24};
	conv2d[1] = new double[width] {1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24};
	conv2d[2] = new double[width] {1.0 / 24, 1.0 / 24, 0       , 1.0 / 24, 1.0 / 24};
	conv2d[3] = new double[width] {1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24};
	conv2d[4] = new double[width] {1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24, 1.0 / 24};
}

unsigned char Smooth::execute(const Image* image, int x, int y, Channel channel, ImagePointRule rule)
{
	double res = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			QColor c = image->pixel(x - width / 2 + j, y - height / 2 + i, rule);
			res += color_in_channel(c, channel) * conv2d[i][j];
		}
	}

	//res /= 2;

	if (res > 255)
		res = 255;
	if (res < 0)
		res = 0;
	return res;
}