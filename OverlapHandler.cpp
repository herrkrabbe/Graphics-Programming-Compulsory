#include "OverlapHandler.h"
#include "ServiceProvider.h"

OverlapHandler::OverlapHandler() {

}

void OverlapHandler::Tick(float deltaTime)
{
    CheckOverlap();
}

void OverlapHandler::AddInteractObject(AbstractInteractObject *object)
{
    interactableObjects.try_emplace(object->getName(), object);
    //check here for pointer bug later. things may be deleted
}

void OverlapHandler::CheckOverlap()
{
    Player* player = ServiceProvider::GetPlayer();


    for(auto objectPair : interactableObjects) {
        AbstractInteractObject* entity = objectPair.second;

        if( !player->CheckOverlap(entity)) continue;

        entity->Interact(player);

    }
}
