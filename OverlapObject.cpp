#include "OverlapObject.h"

void OverlapObject::Deactivate()
{
    bIsActive=0;
    bDisplay=0;
}

OverlapObject::OverlapObject() : VisualObject(), IOverlap() {}

OverlapObject::OverlapObject(std::string name, Vertex OverlapCenter, float radius) : VisualObject(), IOverlap(OverlapCenter, radius)
{
    mName = name;
}

OverlapObject::OverlapObject(Vertex OverlapCenter, float radius, std::string filePath) : VisualObject(filePath), IOverlap(OverlapCenter, radius)
{

}

void OverlapObject::move(float x, float y, float z)
{
    VisualObject::move(x, y, z);
    //IOverlap::OverlapCenter.x += x;
    //IOverlap::OverlapCenter.y += y;
    //IOverlap::OverlapCenter.z += z;
}

void OverlapObject::scale(float s)
{
    VisualObject::scale(s);
    IOverlap::radius *= s;
}

bool OverlapObject::IsActive()
{
    return bIsActive;
}


bool OverlapObject::CanOverlap()
{
    return isVisible();
}

void OverlapObject::ToggleCanOverlap()
{
    //an deactivated object cannot be toggled visible
    if(!bIsActive) return;

    bDisplay = !bDisplay;
}

const Vertex OverlapObject::GetCenter()
{
    //return IOverlap::GetCenter();
    QVector4D homogenousCenter = QVector4D(OverlapCenter.x, OverlapCenter.y, OverlapCenter.z, 1);
    QVector4D transformedCenter = mMatrix * homogenousCenter;
    return {transformedCenter.x(), transformedCenter.y(), transformedCenter.z(), 0, 0, 0, 0, 0};
}
