#include "SceneSwapper.h"
#include "OverlapLogic.h"

SceneSwapper::SceneSwapper(IScene* scene, std::string parentName) : AbstractInteractObject(scene->GetOverlapHandler(), parentName.append("SceneSwapper"), {0, 0, 0, 0, 0, 0, 0, 0}, 1)
{
    SceneSwapper::scene = scene;
}

void SceneSwapper::Interact(IPlayer *interactor)
{
    scene->ToggleScene();
}

void SceneSwapper::ToggleVisible()
{
    //nothing here, because a scene swapper is not visible.
}

bool SceneSwapper::CallOtherOverlapFunction(IOverlap *other)
{
    return other->OverlapWithSphere(GetCenter(), radius);
}

bool SceneSwapper::OverlapWithSphere(Vertex sphereCenter, float sphereRadius)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(sphereCenter.x, sphereCenter.y, sphereCenter.z);
    return OverlapLogic::OverlapSphereSphere(thisCenter, radius, otherCenter, sphereRadius);
}

bool SceneSwapper::OverlapWithAABB(Vertex aabbCenter, float aabbLengthX, float aabbLengthY, float aabbLengthZ)
{
    QVector3D thisCenter(GetCenter().x, GetCenter().y, GetCenter().z);
    QVector3D otherCenter(aabbCenter.x, aabbCenter.y, aabbCenter.z);

    return OverlapLogic::OverlapSphereAxisAlignedBoundingBox(thisCenter, radius, otherCenter, aabbLengthX, aabbLengthY, aabbLengthZ);
}
