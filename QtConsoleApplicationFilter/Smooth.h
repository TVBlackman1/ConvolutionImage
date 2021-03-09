#pragma once

#include "Conv2d.h"

class Smooth : public Conv2d
{
public:
	Smooth();

	virtual unsigned char execute(const Image* image, int x, int y, Channel channel = Channel::BlackAndWhite, ImagePointRule rule = ImagePointRule::Default);
};