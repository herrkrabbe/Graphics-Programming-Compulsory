#include "Pickup.h"
#include "OverlapLogic.h"

void Pickup::Init()
{
    Vertex LeftBottomBack{  -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f};
    Vertex RightBottomBack{  1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f};
    Vertex LeftTopBack{     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
    Vertex RightTopBack{     1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f};
    Vertex LeftBottomFront{ -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f};
    Vertex RightBottomFront{ 1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f};
    Vertex LeftTopFront{    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
    Vertex RightTopFront{    1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f};

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

    texture = "YELLOW";
}

Pickup::Pickup(IOverlapHandler* listner) : AbstractInteractObject(listner, "pickup", {0, 0, 0, 0, 0, 0, 0, 0}, 1.f) {
    Init();
}

Pickup::Pickup(IOverlapHandler* listner, float x, float y, float z, std::string name) : AbstractInteractObject(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 1.f)
{
    bDisplay = 0;
    Init();
    move(x, y, z);
    bDisplay = 1;
}

void Pickup::Tick(float deltaTime)
{
    VisualObject::rotate(deltaTime*100, 0.f, 1.f, 0.f);
}

void Pickup::Interact(IPlayer *interactor)
{
    interactor->AddPoint(1);
    Deactivate();
}

bool Pickup::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool Pickup::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool Pickup::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
