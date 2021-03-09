#include "Image.h"
#include <iostream>

Image::Image(std::string filename)
{
	img = new QImage(QString::fromStdString(filename));
}

Image::Image(QImage& qimage)
{
	setImage(qimage);
}

Image::Image(const Image& image)
{
	img = new QImage(*image.img);
}

Image& Image::operator=(const Image& image)
{
	img = new QImage(*image.img);
	return *this;
}

Image::~Image()
{
	delete img;
	img = nullptr;
}

void Image::setImage(QImage& qimage)
{
	if (img != nullptr)
	{
		delete img;
		img = nullptr;
	}
	img = &qimage;
}

void Image::save(std::string new_filename)
{
	img->save(QString::fromStdString(new_filename));
}

QColor Image::pixel(int x, int y, ImagePointRule rule) const
{
	QColor res;

	switch (rule)
	{
	case ImagePointRule::Border0:
		if (x < 0 || y < 0 || x >= img->width() || y >= img->height())
		{
			res.setRgb(0, 0, 0);
		}
		else
		{
			res.setRgb(img->pixel(x, y));
		}
		break;
	case ImagePointRule::Torus:
		if (x < 0)
		{
			x *= (-1);
			x = (x - 1) % img->width();
			x = img->width() - 1 - x;
		}
		else if (x >= img->width()) x %= img->width();

		if (y < 0)
		{
			y *= (-1);
			y = (y - 1) % img->height();
			y = img->height() - 1 - y;
		}
		else if (y >= img->height()) y %= img->height();

		res.setRgb(img->pixel(x, y));

		break;
	default:
		if (x < 0 || y < 0 || x >= img->width() || y >= img->height())
		{
			throw std::exception("Out of image range");
		}
		else
		{
			res.setRgb(img->pixel(x, y));
		}
		break;
	}
	return res;
}