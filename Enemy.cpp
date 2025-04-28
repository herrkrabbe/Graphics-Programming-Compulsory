#include "Enemy.h"
#include "OverlapLogic.h"
#include <Math.h>

Enemy::Enemy(IOverlapHandler* listner, std::string name, Vertex ControlPoints[]) : AbstractInteractObject(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 1)
{
    bDisplay=0;
    Enemy::Init();
    VisualObject::mName = name;

    Enemy::ControlPoints[0] = ControlPoints[0];
    Enemy::ControlPoints[1] = ControlPoints[1];
    Enemy::ControlPoints[2] = ControlPoints[2];

    Vertex StartPoint = ControlPoints[0];
    move(StartPoint.x, StartPoint.y, StartPoint.z);
    texture = "RED";
    bDisplay=1;
}

void Enemy::Init()
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
}

void Enemy::Tick(float deltaTime)
{
    lifeTime+=deltaTime;
    UpdateT(deltaTime);

    Vertex deltaCoordinates = CalculateVectorToTPoint();

    move(deltaCoordinates.x, deltaCoordinates.y, deltaCoordinates.z);
    //move(0, deltaTime, 0);
}



Vertex Enemy::CalculateTPoint()
{
    float x = (1 - t) * (1 - t) * ControlPoints[0].x + 2 * (1 - t) * t * ControlPoints[1].x + t * t * ControlPoints[2].x;
    float y = (1 - t) * (1 - t) * ControlPoints[0].y + 2 * (1 - t) * t * ControlPoints[1].y + t * t * ControlPoints[2].y;
    float z = (1 - t) * (1 - t) * ControlPoints[0].z + 2 * (1 - t) * t * ControlPoints[1].z + t * t * ControlPoints[2].z;

    return {x, y, z, 0.f, 0.f, 0.f, 0.f, 0.f};
}

void Enemy::UpdateT(float deltaTime)
{
    float amplitude=0.5;
    t = (2 * amplitude / M_PI) * std::asin(std::sin(2 * (M_PI / patrolTime) * lifeTime)) + amplitude;
}

void Enemy::Interact(IPlayer *interactor)
{
    interactor->LoseLife();
}



Vertex Enemy::CalculateVectorToTPoint()
{
    Vertex TPoint = CalculateTPoint();

    float deltaX = TPoint.x-GetCenter().x;
    float deltaY = TPoint.y-GetCenter().y;
    float deltaZ = TPoint.z-GetCenter().z;
    //return {deltaX, deltaY, 0, 0, 0, 0, 0, 0};
    return {deltaX, deltaY, deltaZ, 0, 0, 0, 0, 0};
}

bool Enemy::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool Enemy::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool Enemy::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
