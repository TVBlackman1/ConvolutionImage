#include <iostream>

#include <QtCore/QCoreApplication>
#include "ImageFilter.h"
#include "ImageConvolutor.h"
#include "ShiftRight.h"
#include "Smooth.h"
#include "Invert.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string directory = "C:/Users/vbifm/Desktop/files/";
    std::string filename = "girl.jpg";
    std::string new_filename = "girl2.jpg";

    Image img(directory + filename);

    //ImageConvolutor image_convolutor(img);

    ImageFilter filter(img);

    Conv2d* shift_right = new ShiftRight();
    Conv2d* smooth = new Smooth();
    Conv2d* invert = new Invert();

    filter.apply_filter(smooth, ImagePointRule::Border0);
    filter.apply_filter(smooth, ImagePointRule::Border0);
    filter.apply_filter(invert, ImagePointRule::Default);

    Image new_img = filter.get_image();

    std::cout << new_img.img->width();

    new_img.save(directory + new_filename);

    std::cout << "end" << std::endl;

    return a.exec();
}
