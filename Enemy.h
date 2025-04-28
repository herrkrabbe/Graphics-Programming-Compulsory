#ifndef ENEMY_H
#define ENEMY_H

#include "AbstractInteractObject.h"

/*
 * An enemy patrols a path. If the player overlaps with an enemy, the player will lose
 */
class Enemy : public AbstractInteractObject
{
public:
    Enemy(IOverlapHandler* listner, std::string name, Vertex ControlPoints[3]);
    void Init();

    Vertex ControlPoints[3];
    float t{0};

    virtual void Tick(float deltaTime) override;

private:
    Vertex CalculateVectorToTPoint();
    Vertex CalculateTPoint();
    void UpdateT(float deltaTime);
    float lifeTime{0};
    float patrolTime{5};
    float TGrowthDirection{1};

    // IInteract interface
public:
    void Interact(IPlayer *interactor) override;

    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // ENEMY_H
