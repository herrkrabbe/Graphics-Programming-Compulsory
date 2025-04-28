#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>

#include "Texture.h"

Texture::Texture()
{
    //Default constructor - Make small dummy texture
    makeDummyTexture();
}

Texture::Texture(const std::string& filename)
{
    textureFilename = filename;
    readBitmap(filename);       //reads the BMP into memory
    //bool success = readBitmap(filename);       //reads the BMP into memory
    //if(success)
        //setTexture();               //set texture up for OpenGL
}

unsigned int Texture::id() const
{
    return mId;
}



bool Texture::readBitmap(const std::string &filename)
{
    OBITMAPFILEHEADER bmFileHeader;
    OBITMAPINFOHEADER bmInfoHeader;

    std::string fileWithPath = filename;

    std::ifstream file;
    file.open (fileWithPath.c_str(), std::ifstream::in | std::ifstream::binary);
    if (file.is_open())
    {
        file.read((char *) &bmFileHeader, 14);

        file.read((char *) &bmInfoHeader, sizeof(OBITMAPINFOHEADER));

        if (bmFileHeader.bfType != 19778)
        {
            qDebug("ERROR: File is not a propper BMP file - no BM as first bytes");
            makeDummyTexture();
            return false;
        }

        mColumns = bmInfoHeader.biWidth;
        mRows = bmInfoHeader.biHeight;
        mBytesPrPixel = bmInfoHeader.biBitCount / 8;
        if(mBytesPrPixel == 4)
            mAlphaUsed = true;

        if(mBytesPrPixel <3)    //we only support 24 or 32 bit images
        {
            qDebug("ERROR: Image not 24 or 32 bit RBG or RBGA");
            makeDummyTexture();
            return false;
        }

        mBitmap = new unsigned char[mColumns * mRows * mBytesPrPixel];

        //check if image data is offset - most often not used...
        if(bmFileHeader.bfOffBits !=0)
            file.seekg(bmFileHeader.bfOffBits);
        else if(bmInfoHeader.biSize != 40) //try next trick if file is not a plain old BMP
        {
            int discard = bmInfoHeader.biSize - sizeof(OBITMAPINFOHEADER);
            char* temp = new char[discard];
            file.read( temp, discard);   //discard extra info if header is not old 40 byte header
            qDebug("WARNING: InfoHeader is not 40 bytes, so image might not be correct");
            delete[] temp;
        }
        file.read((char *) mBitmap, mColumns * mRows * mBytesPrPixel);
        file.close();
        return true;
    }
    else
    {
        qDebug() << "ERROR: Can not read " << fileWithPath;
		//Make dummy texture instead
        makeDummyTexture();
    }
    return false;
}

void Texture::makeDummyTexture()
{
    qDebug("Making dummy texture");
    for (int i = 0; i < 16; i++)
        pixels[i] = 0;
    //Set some colors
    pixels[0] = 255;
    pixels[5] = 255;
    pixels[10] = 255;
    pixels[12] = 255;
    pixels[13] = 255;

    mColumns = 2;
	mRows = 2;
    mBytesPrPixel = 4;
    mAlphaUsed = true;

    // mBytesPrPixel = 3;
    // mAlphaUsed = false;


    mBitmap = new unsigned char[mColumns * mRows * mBytesPrPixel];
    memcpy(mBitmap, pixels, mColumns * mRows * mBytesPrPixel);
	//for (int i = 0; i < mColumns * mRows * mBytesPrPixel; i++)
	//	mBitmap[i] = pixels[i];
}
