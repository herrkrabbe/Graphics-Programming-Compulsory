#ifndef DOOR_H
#define DOOR_H

#include "AbstractInteractObject.h"
#include "IScene.h"
#include "SceneSwapper.h"

/**
 * A door will open when the player approaches.
 * The door holds a SceneSwapper to handle logic to enter the door
 */
class Door : public AbstractInteractObject
{
private:
    SceneSwapper* sceneSwapper;
    bool isOpen{0};
    void ToggleOpen();

    void Init();
public:
    Door(IScene* scene, float x, float y, float z, std::string name);

    // VisualObject interface
public:
    virtual void Tick(float deltaTime) override;

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;

    // VisualObject interface
public:
    virtual void move(float x, float y, float z) override;


    // IOverlap interface
public:
    virtual void ToggleCanOverlap() override;

    // IOverlap interface
public:
    virtual bool CallOtherOverlapFunction(IOverlap *other) override;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) override;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) override;
};

#endif // DOOR_H
