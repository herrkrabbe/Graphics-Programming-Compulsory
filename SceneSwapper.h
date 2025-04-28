#ifndef SCENESWAPPER_H
#define SCENESWAPPER_H

#include "AbstractInteractObject.h"
#include "IScene.h"

/*
 * An object which toggles the visibility of the scene when interacted with.
 */
class SceneSwapper : public AbstractInteractObject
{
private:
    IScene* scene;
public:
    SceneSwapper(IScene* scene, std::string parentName);

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;

    // VisualObject interface
public:
    virtual void ToggleVisible() override;

    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // SCENESWAPPER_H
