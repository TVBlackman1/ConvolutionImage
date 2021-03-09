#pragma once

#include "Conv2d.h"

class Invert : public Conv2d
{
public:
	Invert();

	virtual unsigned char execute(const Image* image, int x, int y, Channel channel = Channel::BlackAndWhite, ImagePointRule rule = ImagePointRule::Default);
};