#ifndef IOVERLAP_H
#define IOVERLAP_H

#include "vertex.h"

/*
Interface used to provide the functions needed to allow an object to overlap with other object.
This interface is not responsible to check if all objects are overlapping.
*/
class IOverlap {
protected:
    Vertex OverlapCenter;
    float radius{0.f};
    IOverlap() {
        OverlapCenter = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    };

    IOverlap(Vertex center, float radius) {
        OverlapCenter = center;
        IOverlap::radius = radius;
    };
    bool bCanOverlap{1};

public:
    virtual bool CheckOverlap(IOverlap* other) {
        if(other == this) return 0; // an object cannot overlap with itself
        if(!CanOverlap()) return false;
        if(!other->CanOverlap()) return false;

        bool result = CallOtherOverlapFunction(other);

        return result;

    }
    virtual bool CallOtherOverlapFunction(IOverlap* other) = 0;
    virtual bool OverlapWithSphere(Vertex sphereCenter, float sphereRadius) = 0;
    virtual bool OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ) = 0;

    virtual void ToggleCanOverlap() = 0;

    virtual bool CanOverlap() {return bCanOverlap;}

    virtual Vertex const GetCenter() {return OverlapCenter;}
};

#endif // IOVERLAP_H
