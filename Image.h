#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <string>


class Image
{
public:
    Image(std::string filepath);

    int GetWidth();
    int GetHeight();
    QRgb GetValue(int x, int y);
    QRgb GetValueFromUV(float u, float v);
private:
    QImage image;
};

#endif // IMAGE_H
