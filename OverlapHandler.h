#ifndef OVERLAPHANDLER_H
#define OVERLAPHANDLER_H

#include "IOverlapHandler.h"

/*
 * The OverlapHandler lazily checks if the player character is overlapping with every
 * object in the scene.
 */
class OverlapHandler : public IOverlapHandler
{
private:
    std::map<std::string, AbstractInteractObject*> interactableObjects;
public:
    OverlapHandler();

    // IOverlapHandler interface
public:
    virtual void Tick(float deltaTime) override;
    virtual void AddInteractObject(AbstractInteractObject *object) override;
    std::map<std::string, AbstractInteractObject*> GetInteractableObjects() override {return interactableObjects;}
private:
    void CheckOverlap();
};

#endif // OVERLAPHANDLER_H
