#ifndef OVERLAPLOGIC_H
#define OVERLAPLOGIC_H
#include <QVector3D>


namespace OverlapLogic {
bool OverlapSphereSphere(QVector3D centerOne, float radiusOne, QVector3D centerTwo, float radiusTwo);

bool OverlapSphereAxisAlignedBoundingBox(QVector3D sphereCenter, float sphereRadius, QVector3D AABBCenter, float AABBLengthX, float AABBLengthY, float AABBLengthZ);

bool OverlapAABBAABB(QVector3D centerOne, float lengthXOne, float lenthYOne, float lengthZOne, QVector3D centerTwo, float lengthXTwo, float lengthYTwo, float lengthZTwo);
}

#endif // OVERLAPLOGIC_H
