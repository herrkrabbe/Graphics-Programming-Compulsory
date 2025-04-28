#include "Image.h"

Image::Image(std::string filepath) {
    bool validPath = image.load(filepath.c_str());
    if(!validPath) {
        throw;
    }
    image = QImage(filepath.c_str());
}

int Image::GetWidth()
{
    return image.width();
}

int Image::GetHeight()
{
    return image.height();
}

QRgb Image::GetValue(int x, int y)
{
    bool validX = image.valid(x, 0);
    bool validY = image.valid(0, y);

    assert(validX);
    assert(validY);

    return image.pixel(x, y);
}

QRgb Image::GetValueFromUV(float u, float v)
{
    int x = u*(GetWidth()-1);
    int y = v*(GetHeight()-1);
    return GetValue(x, y);
}
