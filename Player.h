#ifndef PLAYER_H
#define PLAYER_H

#include "IControl.h"
#include "IPlayer.h"
#include "OverlapObject.h"

/*
 * The Player character is an OverlapObject which can recieve controller input
 * and can interact with the other objects in the scene.
 */
class Player : public OverlapObject, public IPlayer, public IControl
{
private:
    int points{0};
protected:
    KeyState keyState;
    float MovementUnitsPerSecond{4};
private:
    void Init();
    void MoveFromInput(float deltaTime);
public:
    Player();
    virtual void Tick(float deltaTime) override;
    virtual void move(float x, float y, float z) override;

    // IPlayer interface
public:
    void LoseLife() override;
    void AddPoint(int points) override;
    int GetPoints() override;
    QVector3D GetPosition() override;
    void PushPlayer(QVector3D pushVector) override;
    float GetRadius() override;

    // IControl interface
public:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // PLAYER_H
