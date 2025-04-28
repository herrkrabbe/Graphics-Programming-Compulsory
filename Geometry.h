#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>
namespace barysentric2D {

// QVector3D carthesianToBarisentric(float x, float y, QVector2D point1, QVector2D point2, QVector2D point3) {
    // float determinant = (point2.y()-point3.y())*(point1.x()-point3.x()) + (point3.x() - point2.x())*(point1.y()-point3.y());
    // float lambdaOne = (   (point2.y() - point3.y())*(x - point3.x()) - (point3.x() - point2.x())*(y - point3.y())   ) / determinant;
    // float lambdaTwo = (   (point3.y() - point1.y())*(x - point3.x()) - (point1.x() - point3.x())*(y - point3.y())   ) / determinant;
    // float lambdaThree = 1 - lambdaOne - lambdaTwo;
    // return {lambdaOne, lambdaTwo, lambdaThree};
// }

// Function to calculate the area of the triangle formed by points (x1, y1), (x2, y2), and (x3, y3)
float area(QVector2D A, QVector2D B, QVector2D C) {
    return 0.5f * std::abs(A.x() * (B.y() - C.y()) + B.x() * (C.y() - A.y()) + C.x() * (A.y() - B.y()));
}

// Function to convert a Cartesian coordinate (px, py) to barycentric coordinates
QVector3D cartesianToBarycentric(float x, float y, QVector2D T1, QVector2D T2, QVector2D T3) {
    // Area of the full triangle
    float A_total = area(T1, T2, T3);

    QVector2D P(x, y);

    // Area of the triangle with point P and vertices T2, T3
    float A_P_T2_T3 = area(P, T2, T3);
    // Area of the triangle with point P and vertices T1, T3
    float A_P_T1_T3 = area(P, T1, T3);
    // Area of the triangle with point P and vertices T1, T2
    float A_P_T1_T2 = area(P, T1, T2);

    float bX = A_P_T2_T3 / A_total;;
    float bY = A_P_T1_T3 / A_total;;
    float bZ = A_P_T1_T2 / A_total;;

    QVector3D coordinates(bX, bY, bZ);

    return coordinates;
}

bool IsInsideTriangle(float x, float y, QVector2D point1, QVector2D point2, QVector2D point3) {
    QVector3D coordinates = cartesianToBarycentric(x, y, point1, point2, point3);
    bool isInside = true;
    if(coordinates.x() < 0) {
        isInside = false;
    }
    if(coordinates.y() < 0) {
        isInside = false;
    }
    if(coordinates.z() < 0) {
        isInside = false;
    }
    return isInside;
}
}

namespace plane {
std::tuple<float, float, float, float> MakePlane(QVector3D point1, QVector3D point2, QVector3D point3) {
    QVector3D vector1 = point2-point1;
    QVector3D vector2 = point3-point1;
    QVector3D normal = QVector3D::crossProduct(vector1, vector2);
    float a = normal.x();
    float b = normal.y();
    float c = normal.z();
    float d = 0 - a*point1.x() - b*point1.y() - c*point1.z();
    return {a, b, c, d};
}

float GetZFromXY(float x, float y, QVector3D point1, QVector3D point2, QVector3D point3) {
    //plane: ax + by +cz + d = 0
    //tuple<a, b, c, d>
    std::tuple<float, float, float, float> plane = MakePlane(point1, point2, point3);

    //z = -(ax + by +d)/c
    float z = -(std::get<0>(plane)*x + std::get<1>(plane)*y + std::get<3>(plane))/std::get<2>(plane);
    return z;
}
}

#endif // GEOMETRY_H
