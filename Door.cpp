#include "Door.h"
#include "OverlapLogic.h"


void Door::ToggleOpen()
{
    isOpen = !isOpen;
    rotate(90, 0, 0, 1);
}

void Door::Init()
{
    Vertex LeftBottomBack{  -0.5f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f};
    Vertex RightBottomBack{  0.5f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f};
    Vertex LeftTopBack{     -0.5f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f};
    Vertex RightTopBack{     0.5f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f};
    Vertex LeftBottomFront{ -0.5f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f};
    Vertex RightBottomFront{ 0.5f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f};
    Vertex LeftTopFront{    -0.5f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f};
    Vertex RightTopFront{    0.5f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f};

    mVertices.push_back(LeftBottomBack);
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(LeftTopBack);
    mVertices.push_back(RightTopBack);
    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(RightBottomFront);
    mVertices.push_back(LeftTopFront);
    mVertices.push_back(RightTopFront);

    //Right
    mIndices.push_back(6);
    mIndices.push_back(1);
    mIndices.push_back(3);

    mIndices.push_back(6);
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

Door::Door(IScene *scene, float x, float y, float z, std::string name) : AbstractInteractObject(scene->GetOverlapHandler(), name, {0, 0, 0, 0, 0, 0, 0, 0}, 6)
{
    bDisplay=0;

    sceneSwapper = new SceneSwapper(scene, mName);
    Init();
    Door::move(x, y, z);
    texture = "BLUE";

    bDisplay=1;
}

void Door::Tick(float deltaTime)
{
    AbstractInteractObject::Tick(deltaTime);
    sceneSwapper->Tick(deltaTime);
    //VisualObject::rotate(deltaTime*100, 0.f, 1.f, 0.f);
}

void Door::Interact(IPlayer *interactor)
{
    float xDirection = interactor->GetPosition().x() - GetCenter().x;
    float yDirection = interactor->GetPosition().y() - GetCenter().y;
    float zDirection = interactor->GetPosition().z() - GetCenter().z;

    QVector3D vectorToPlayer = QVector3D(xDirection, yDirection, zDirection);
    float distance = vectorToPlayer.length();

    //open if closed
    if
        (
            ( distance < (radius - 1) )
            &&
            ( !isOpen )
        )
    {
        ToggleOpen();
        return;
    }

    //close if open
    if
        (
            ( distance >= (radius - 1) )
            &&
            ( isOpen )
        )
    {
        ToggleOpen();
        return;
    }
}

void Door::move(float x, float y, float z)
{
    OverlapObject::move(x, y, z);
    sceneSwapper->move(x, y, z);
}

void Door::ToggleCanOverlap()
{
    OverlapObject::ToggleCanOverlap();
    sceneSwapper->ToggleCanOverlap();
}

bool Door::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool Door::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool Door::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
