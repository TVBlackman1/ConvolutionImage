#pragma once

#include "Image.h"
#include "ImageConvolutor.h"
#include <iostream>
#include <thread>
#include <condition_variable>

enum class ImageProcessingType
{
	RGB,
	BlackAndWhite
};

class ImageFilter
{
	Image* img;
	ImageProcessingType type;
	ImageConvolutor** convolutors;
	int count_convs;

public:
	ImageFilter(const Image& img, ImageProcessingType image_type = ImageProcessingType::RGB, ImagePointRule rule = ImagePointRule::Default)
	{
		this->img = new Image(img);
		type = image_type;

		switch (type)
		{
		default:
		case ImageProcessingType::RGB:
			count_convs = 3;
			convolutors = new ImageConvolutor * [count_convs];
			convolutors[0] = new ImageConvolutor(img, Channel::Red);
			convolutors[1] = new ImageConvolutor(img, Channel::Green);
			convolutors[2] = new ImageConvolutor(img, Channel::Blue);
			break;
		case ImageProcessingType::BlackAndWhite:
			count_convs = 1;
			convolutors = new ImageConvolutor * [count_convs];
			convolutors[0] = new ImageConvolutor(img, Channel::BlackAndWhite);
			break;
		}
	}

	void apply_filter(Conv2d* conv, ImagePointRule rule = ImagePointRule::Default)
	{
		//std::thread* threads = new std::thread[count_convs];

		for (int i = 0; i < count_convs; i++)
		{
			//threads[i] = std::thread(
			//	[this](int index, Conv2d* conv, ImagePointRule rule = ImagePointRule::Default)
			//	{
			//		convolutors[index]->convolute(conv, rule);
			//	}, i, conv, rule);

			convolutors[i]->convolute(conv, rule);
		}
		std::cout << "applied filter" << std::endl;
	}

	Image get_image()
	{
		std::cout << "start getting new image" << std::endl;

		QImage* new_qimage = new QImage(img->img->width(), img->img->height(), img->img->format());
		for (int i = 0; i < img->img->width(); i++)
		{
			for (int j = 0; j < img->img->height(); j++)
			{
				QColor pix(0, 0, 0);
				for (int k = 0; k < count_convs; k++)
				{
					unsigned char char_color_from_black_and_white = convolutors[k]->get_image().pixel(i, j).red();
					QColor channel_color = char_to_color_in_channel(char_color_from_black_and_white, convolutors[k]->get_channel());

					pix = color_sum(pix, channel_color);
				}
				new_qimage->setPixelColor(QPoint(i, j), pix);
				//std::cout << pix.red() << " " << pix.green() << " " << pix.blue() << std::endl;
			}
		}

		std::cout << "end getting new image" << std::endl;
		Image ret(*new_qimage);
		std::cout << ret.img->width();
		return ret;
	}
};

