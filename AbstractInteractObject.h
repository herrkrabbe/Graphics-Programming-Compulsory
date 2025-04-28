#ifndef ABSTRACTINTERACTOBJECT_H
#define ABSTRACTINTERACTOBJECT_H

#include "IInteract.h"
#include "OverlapObject.h"
class IOverlapHandler;

/*
 * A class describing objects which can be collided with and interacted with.
 */
class AbstractInteractObject : public IInteract, public OverlapObject
{
protected:
    IOverlapHandler* listner;
    void AddOverlapListner(IOverlapHandler* listner);
    AbstractInteractObject(IOverlapHandler *listner, std::string name, Vertex OverlapCenter, float radius);
    AbstractInteractObject(IOverlapHandler *listner, Vertex OverlapCenter, float radius, std::string filePath);


};

#endif // ABSTRACTINTERACTOBJECT_H
