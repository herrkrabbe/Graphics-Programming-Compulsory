#ifndef GROUND_H
#define GROUND_H

#include "Image.h"
#include "Texture.h"
#include "VisualObject.h"

class Ground : public VisualObject
{
public:
    //Ground(QVector3D initialPosition, TextureHandle heightMap, float quadSize);
    Ground(QVector3D initialPosition, float quadSize, float maxHeight);

    float GetHeightFromWorldPos(const float x, const float y);
    bool PositionIsInsideArea(const float x, const float y);

    /*
     * check if zero-indexed column and row are inside the area of the
     * ground.
     */
    bool PositionIsInsideArea(const int col, const int row);

    /*
     * Get the column and row of quads the position would be inside. If the
     * position is outside the triangle, it will still return a
     * column and row. Use PositionIsInsideArea(int, int) to check
     * if column and row are valid.
     */
    std::tuple<int, int> GetColRowFromPos(const float x, const float y);

private:
    void Init(float quadSize, float maxHeight);
    // void Init(TextureHandle heightMap, float quadSize);
    void CreateTriangles(float maxHeight);
    //TextureHandle heightMap;
    Image* heightMap;
    float quadSize;
};

#endif // GROUND_H
