#ifndef PICKUP_H
#define PICKUP_H

#include "AbstractInteractObject.h"

/*
 * A pickup spins in place, and gives the player one point when interacted with.
 */
class Pickup : public AbstractInteractObject
{
private:
    void Init();
public:
    Pickup(IOverlapHandler* listner);
    Pickup(IOverlapHandler* listner, float x, float y, float z, std::string name);

    // OverlapObject interface
public:
    void Tick(float deltaTime) override;

    // IInteract interface
public:
    void Interact(IPlayer *interactor) override;

    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // PICKUP_H
