#include "Player.h"
#include "ServiceProvider.h"
#include "OverlapLogic.h"

void Player::Init()
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

void Player::MoveFromInput(float deltaTime)
{
    QVector2D movementDirection;

    if(keyState.W) {
        movementDirection.setX(1);
    }
    if(keyState.D) {
        movementDirection.setY(1);
    }
    if(keyState.S) {
        movementDirection.setX( ( movementDirection.x() - 1 ) );
    }
    if(keyState.A) {
        movementDirection.setY( ( movementDirection.y() - 1 ) );
    }

    if(movementDirection.x() == 0 && movementDirection.y() == 0) {
        return;
    }
    movementDirection.normalize();



    float xDistance = movementDirection.x() * deltaTime * MovementUnitsPerSecond;
    float zDistance = movementDirection.y() * deltaTime * MovementUnitsPerSecond;


    //move(xDistance, 0, zDistance);
    move(zDistance, xDistance, 0);
}

// Player::Player() : OverlapObject("Player", {0, 0, 0, 0, 0, 0, 0, 0}, 1) {
//     Init();
//     texture = "GREEN";
// }

Player::Player() : OverlapObject({0, 0, 0, 0, 0, 0, 0, 0}, 0.410156, "../../Meshes/suzanne.obj") {
    mName = "Player";
    texture = "GREEN";
    drawType = 1;

}

void Player::Tick(float deltaTime)
{

    if(!IsActive()) return;

    MoveFromInput(deltaTime);


}

void Player::move(float x, float y, float z)
{
    OverlapObject::move(x, y, z);

    if(ServiceProvider::HasCamera()) {
        ServiceProvider::GetCamera()->moveRight(-x);
        ServiceProvider::GetCamera()->updateHeigth(-y);
    }

}

void Player::LoseLife()
{
    qDebug("You lost\n");
    std::cout << "You lost\n";
    Deactivate();
}

void Player::AddPoint(int points)
{
    Player::points+=points;
    qDebug() << Player::points << " of 7 pickups are collected\n";
}

int Player::GetPoints()
{
    return points;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_W:
        keyState.W=1;
        break;
    case Qt::Key_A:
        keyState.A=1;
        break;
    case Qt::Key_S:
        keyState.S=1;
        break;
    case Qt::Key_D:
        keyState.D=1;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_W:
        keyState.W=0;
        break;
    case Qt::Key_A:
        keyState.A=0;
        break;
    case Qt::Key_S:
        keyState.S=0;
        break;
    case Qt::Key_D:
        keyState.D=0;
        break;
    }
}

QVector3D Player::GetPosition()
{
    float x = mMatrix.column(3).x();
    float y = mMatrix.column(3).y();
    float z = mMatrix.column(3).z();

    return QVector3D(x, y, z);
}

void Player::PushPlayer(QVector3D pushVector)
{
    move(pushVector.x(), pushVector.y(), pushVector.z());
}

float Player::GetRadius()
{
    return radius;
}

bool Player::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool Player::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool Player::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
