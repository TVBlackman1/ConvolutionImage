#pragma once

#include <qpixmap.h>
#include <qimage.h>
//#include "Conv2d.h"
//#include "ShiftRight.h"


enum class ImagePointRule
{
	Default,
	Border0,
	Torus
};

class Image
{
public:
	QImage* img = nullptr;
	Image(std::string filename);

	Image(QImage& qimage);

	Image(const Image& image);

	Image& operator=(const Image& image);

	~Image();

	void save(std::string new_filename);

	void setImage(QImage& qimage);


	QColor pixel(int x, int y, ImagePointRule rule = ImagePointRule::Default) const;
};

