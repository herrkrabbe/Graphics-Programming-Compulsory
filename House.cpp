#include "House.h"
#include "OverlapLogic.h"

void House::Init()
{
    Vertex LeftBottomBack{  -4.0f, -4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomBack{  4.0f, -4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopBack{     -4.0f,  4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopBack{     4.0f,  4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftBottomFront{ -4.0f, -4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomFront{ 4.0f, -4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopFront{    -4.0f,  4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopFront{    4.0f,  4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};

    mVertices.push_back(LeftBottomBack);
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(LeftTopBack);
    mVertices.push_back(RightTopBack);
    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(RightBottomFront);
    mVertices.push_back(LeftTopFront);
    mVertices.push_back(RightTopFront);

    //Right
    mIndices.push_back(5);
    mIndices.push_back(1);
    mIndices.push_back(3);

    mIndices.push_back(5);
    mIndices.push_back(3);
    mIndices.push_back(7);

    //Left
    mIndices.push_back(0);
    mIndices.push_back(4);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(4);
    mIndices.push_back(6);

    //Top
    mIndices.push_back(6);
    mIndices.push_back(7);
    mIndices.push_back(3);
    mIndices.push_back(6);
    mIndices.push_back(3);
    mIndices.push_back(2);

    //Bottom
    mIndices.push_back(1);
    mIndices.push_back(5);
    mIndices.push_back(4);
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(4);

    //Front
    mIndices.push_back(4);
    mIndices.push_back(5);
    mIndices.push_back(7);
    mIndices.push_back(4);
    mIndices.push_back(7);
    mIndices.push_back(6);

    //Back
    mIndices.push_back(3);
    mIndices.push_back(1);
    mIndices.push_back(0);
    mIndices.push_back(0);
    mIndices.push_back(2);
    mIndices.push_back(3);
}

House::House(IOverlapHandler *listner, float x, float y, float z, std::string name) : AbstractInteractObject(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 4)
{
    bDisplay=0;

    Init();
    move(x, y, z);

    texture = "BROWN";

    bDisplay=1;
}

void House::Interact(IPlayer *interactor)
{
    float xDirection = interactor->GetPosition().x() - GetCenter().x;
    float yDirection = interactor->GetPosition().y() - GetCenter().y;
    float zDirection = interactor->GetPosition().z() - GetCenter().z;

    QVector3D vectorToPlayer = QVector3D(xDirection, yDirection, zDirection);
    float pushDistance = radius + interactor->GetRadius() - vectorToPlayer.length();
    if( pushDistance < 0 ) return;

    QVector3D noramlisedVectorToPlayer = vectorToPlayer.normalized();

    QVector3D pushVector = noramlisedVectorToPlayer*pushDistance;

    interactor->PushPlayer(pushVector);
}

bool House::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool House::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool House::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
