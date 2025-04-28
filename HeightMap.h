#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "VisualObject.h"

class HeightMap : public VisualObject
{
public:
    HeightMap();

    void makeTerrain(unsigned char* textureData, int width, int height);
};

#endif // HEIGHTMAP_H
