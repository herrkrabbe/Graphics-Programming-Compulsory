#include "AbstractInteractObject.h"
#include "IOverlapHandler.h"


AbstractInteractObject::AbstractInteractObject(IOverlapHandler *listner, std::string name, Vertex OverlapCenter, float radius) : OverlapObject{name, OverlapCenter, radius}
{
    AddOverlapListner(listner);
}

AbstractInteractObject::AbstractInteractObject(IOverlapHandler *listner, Vertex OverlapCenter, float radius, std::string filePath) : OverlapObject{OverlapCenter, radius, filePath}
{
    AddOverlapListner(listner);
}

void AbstractInteractObject::AddOverlapListner(IOverlapHandler* listner)
{
    AbstractInteractObject::listner = listner;
    listner->AddInteractObject(this);
}
