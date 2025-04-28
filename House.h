#ifndef HOUSE_H
#define HOUSE_H

#include "AbstractInteractObject.h"

/*
 * A house will push the player away from it if they overlap.
 */
class House : public AbstractInteractObject
{
private:
    void Init();
public:
    House(IOverlapHandler* listner, float x, float y, float z, std::string name);

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;

    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // HOUSE_H
