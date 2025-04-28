#include "OverlapLogic.h"

bool OverlapLogic::OverlapSphereSphere(QVector3D centerOne, float radiusOne, QVector3D centerTwo, float radiusTwo) {
    float deltaX = centerOne.x() - centerTwo.x();
    float deltaY = centerOne.y() - centerTwo.y();
    float deltaZ = centerOne.z() - centerTwo.z();
    float distance = sqrt( pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2) );

    float overlapDistance = abs(radiusOne) + abs(radiusTwo);

    if(distance < overlapDistance) return 1;
    return 0;
}

bool OverlapLogic::OverlapSphereAxisAlignedBoundingBox(QVector3D sphereCenter, float sphereRadius, QVector3D AABBCenter, float AABBLengthX, float AABBLengthY, float AABBLengthZ) {
    bool overlapX = false;
    bool overlapY = false;
    bool overlapZ = false;

    if(sphereCenter.x()+sphereRadius > AABBCenter.x()-AABBLengthX/2) {
        overlapX = true;
    }
    if(sphereCenter.x()-sphereRadius < AABBCenter.x()+AABBLengthX/2) {
        overlapX = true;
    }

    if(sphereCenter.y()+sphereRadius > AABBCenter.y()-AABBLengthY/2) {
        overlapY = true;
    }
    if(sphereCenter.y()-sphereRadius < AABBCenter.y()+AABBLengthY/2) {
        overlapY = true;
    }

    if(sphereCenter.z()+sphereRadius > AABBCenter.z()-AABBLengthZ/2) {
        overlapZ = true;
    }
    if(sphereCenter.z()-sphereRadius < AABBCenter.z()+AABBLengthZ/2) {
        overlapZ = true;
    }

    bool overlaps = overlapX && overlapY && overlapZ;
    return overlaps;
}

bool OverlapLogic::OverlapAABBAABB(QVector3D centerOne, float lengthXOne, float lenthYOne, float lengthZOne, QVector3D centerTwo, float lengthXTwo, float lengthYTwo, float lengthZTwo) {
    bool overlapX = false;
    bool overlapY = false;
    bool overlapZ = false;

    if(centerOne.x()+lengthXOne/2 > centerTwo.x()-lengthXTwo/2) {
        overlapX = true;
    }
    if(centerOne.x()-lengthXOne/2 < centerTwo.x()+lengthXTwo/2) {
        overlapX = true;
    }

    if(centerOne.y()+lenthYOne/2 > centerTwo.y()-lengthYTwo/2) {
        overlapY = true;
    }
    if(centerOne.y()-lenthYOne/2 < centerTwo.y()+lengthYTwo/2) {
        overlapY = true;
    }

    if(centerOne.z()+lengthZOne/2 > centerTwo.z()-lengthZTwo/2) {
        overlapZ = true;
    }
    if(centerOne.z()-lengthZOne/2 < centerTwo.z()+lengthZTwo/2) {
        overlapZ = true;
    }

    bool overlaps = overlapX && overlapY && overlapZ;
    return overlaps;
}
