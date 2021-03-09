#pragma once

#include "Image.h"
#include "Conv2d.h"
#include <iostream>
#include <qpixmap.h>

class ImageConvolutor
{
	Image* img;
	Channel channel;
public:
	ImageConvolutor(const Image& img, Channel channel = Channel::BlackAndWhite)
	{
		this->img = new Image(img);
		this->channel = channel;
	}
	void convolute(Conv2d* conv, ImagePointRule rule = ImagePointRule::Default)
	{
		int width = img->img->width();
		int height = img->img->height();

		QImage* new_qimage = new QImage(width, height, img->img->format());

		for (int i = 0; i < img->img->width(); i++)
		{
			for (int j = 0; j < img->img->height(); j++)
			{
				unsigned char value = conv->execute(img, i, j, channel, rule);
				new_qimage->setPixelColor(QPoint(i, j), QColor(value, value, value));
			}
		}
		delete img;


		img = new Image(*new_qimage);
	}

	Channel get_channel()
	{
		return channel;
	}

	Image get_image()
	{
		return Image(*img);
	}
};

