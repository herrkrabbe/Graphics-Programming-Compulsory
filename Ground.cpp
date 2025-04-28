#include "Ground.h"
#include "Geometry.h"



Ground::Ground(QVector3D initialPosition, float quadSize, float maxHeight) : VisualObject()
{
    bDisplay = 0;
    moveToGround = false;
    //Init(heightMap, quadSize);
    Init(quadSize, maxHeight);
    move(initialPosition.x(), initialPosition.y(), initialPosition.z());
    //texture = "../../Assets/Heightmap.jpg";
    texture = "../../Assets/Boop.jpg";
    bDisplay=1;
}

float Ground::GetHeightFromWorldPos(float x, float y)
{
    float z = mMatrix.column(3).z();
    if(!PositionIsInsideArea(x, y)) {
        return z;
    }
    std::tuple colRow = GetColRowFromPos(x, y);
    int col = std::get<0>(colRow);
    int row = std::get<1>(colRow);

    int indexOne = (col) + (row)*heightMap->GetWidth();
    int indexTwo = (col) + (row+1)*heightMap->GetWidth();
    int indexThree = (col+1) + (row+1)*heightMap->GetWidth();
    int indexFour = (col+1) + (row)*heightMap->GetWidth();

    QVector4D point1(mVertices[indexOne].x, mVertices[indexOne].y, mVertices[indexOne].z, 1);
    QVector4D point2(mVertices[indexTwo].x, mVertices[indexTwo].y, mVertices[indexTwo].z, 1);
    QVector4D point3(mVertices[indexThree].x, mVertices[indexThree].y, mVertices[indexThree].z, 1);
    QVector4D point4(mVertices[indexFour].x, mVertices[indexFour].y, mVertices[indexFour].z, 1);

    point1 = mMatrix*point1;
    point2 = mMatrix*point2;
    point3 = mMatrix*point3;
    point4 = mMatrix*point4;

    bool isInsideTriangleOne = barysentric2D::IsInsideTriangle(x, y, point1.toVector2D(), point2.toVector2D(), point3.toVector2D());
    bool isInsideTriangleTwo = barysentric2D::IsInsideTriangle(x, y, point1.toVector2D(), point3.toVector2D(), point4.toVector2D());

    if(!(isInsideTriangleOne || isInsideTriangleTwo)) {
        return z;
    }

    if(isInsideTriangleOne) {
        z += plane::GetZFromXY(x, y, point1.toVector3D(), point2.toVector3D(), point3.toVector3D());
    }
    else {
        z += plane::GetZFromXY(x, y, point1.toVector3D(), point3.toVector3D(), point4.toVector3D());
    }

    return z;
}

bool Ground::PositionIsInsideArea(const float x, const float y)
{
    std::tuple<int, int> colRow = GetColRowFromPos(x, y);
    int col = std::get<0>(colRow);
    int row = std::get<1>(colRow);
    return PositionIsInsideArea(col, row);
}

bool Ground::PositionIsInsideArea(const int col, const int row)
{
    int maxWidth = (heightMap->GetWidth()-1);
    int maxHeight = (heightMap->GetHeight()-1);

    bool isInside = true;
    if(col < 0) {
        isInside = false;
    }
    else if(row < 0) {
        isInside = false;
    }
    else if(col >= maxWidth) {
        isInside = false;
    }
    else if(row >= maxHeight) {
        isInside = false;
    }
    return isInside;
}

std::tuple<int, int> Ground::GetColRowFromPos(const float x, const float y)
{
    float pivotX = mMatrix.column(3).x();
    float pivotY = mMatrix.column(3).y();
    float relativeX = x - pivotX;
    float relativeY = y - pivotY;

    float floatCol = relativeX/quadSize;
    float floatRow = relativeY/quadSize;

    int col = int(floor(floatCol));
    int row = int(floor(floatRow));

    return {col, row};
}

void Ground::Init(float quadSize, float maxHeight)
{
    Ground::quadSize = quadSize;
    heightMap = new Image("../../Assets/Heightmap.jpg");

    CreateTriangles(maxHeight);
}

void Ground::CreateTriangles(float maxHeight)
{

    //int numVertX = heightMap->width();
    //int numVertY = heightMap->height();
    int numVertX = 256;
    int numVertY = 256;
    for(int j=0; j< numVertY; j++) {
        for(int i = 0; i < numVertX; i++) {

            //create vertices

            float u = float(i)/float(numVertX);
            float v = 1.f - float(j)/float(numVertY);

            QRgb heightValue = heightMap->GetValueFromUV(u, v);
            float height = float(qGray(heightValue))/255 * maxHeight;

            float x = i*quadSize;
            float y = j*quadSize;
            float z = height;

            float r = float(i)/float(numVertX);
            float b = float(j)/float(numVertY);

            mVertices.push_back( {x, y, z, r, 0.f, b, u, v} );

            //create indices
            if(i == numVertX-1 || j == numVertY-1) continue;

            int indexOne = (i) + (j)*numVertX;
            int indexTwo = (i) + (j+1)*numVertX;
            int indexThree = (i+1) + (j+1)*numVertX;
            int indexFour = (i+1) + (j)*numVertX;
            mIndices.push_back(indexOne);
            mIndices.push_back(indexTwo);
            mIndices.push_back(indexThree);

            mIndices.push_back(indexOne);
            mIndices.push_back(indexThree);
            mIndices.push_back(indexFour);
        }
    }
}
