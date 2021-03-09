#pragma once

#include "Conv2d.h"

class ShiftRight : public Conv2d
{
public:
	ShiftRight();

	virtual unsigned char execute(const Image* image, int x, int y, Channel channel = Channel::BlackAndWhite, ImagePointRule rule = ImagePointRule::Default);
};