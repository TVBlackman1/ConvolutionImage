#pragma once

#include "Image.h"
#include "Channel.h"

class Conv2d
{
public:
	int width;
	int height;
	double** conv2d;

public:
	virtual int get_width();

	virtual int get_height();

	virtual unsigned char execute(const Image* image, int x, int y, Channel channel = Channel::BlackAndWhite, ImagePointRule rule = ImagePointRule::Default) = 0;
};