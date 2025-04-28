#include "SceneOne.h"

#include "Door.h"
#include "Enemy.h"
#include "House.h"
#include "OverlapHandler.h"
#include "Pickup.h"
#include "ServiceProvider.h"
#include "TriangleSurface.h"



SceneOne::SceneOne()
{
    overlapHandler = new OverlapHandler();

    //TriangleSurface* Background = new TriangleSurface();
    //Background->setName("Background");
    QVector3D backgroundPos = QVector3D(-14, -14, 0);
    Ground* background = new Ground(backgroundPos, 0.15, 40);
    objects.push_back(background);
    ServiceProvider::SetGround(background);

    Pickup* PickupOne = new Pickup(overlapHandler, 7, -10, -30, "Pickup1");
    Pickup* PickupTwo = new Pickup(overlapHandler, -7, -10, -30, "Pickup2");
    Pickup* PickupThree = new Pickup(overlapHandler, -7, 0, -30, "Pickup3");

    Pickup* PickupFour = new Pickup(overlapHandler, 7, 0, -30, "Pickup4");
    Pickup* PickupFive = new Pickup(overlapHandler, 7, 10, -30, "Pickup5");
    Pickup* PickupSix = new Pickup(overlapHandler, -7, 10, -30, "Pickup6");

    Pickup* PickupSeven = new Pickup(overlapHandler, 18, 0, -30, "Pickup7");
    PickupSeven->ToggleVisible();

    Vertex PatrolOne[3] = {PickupOne->GetCenter(), PickupTwo->GetCenter(), PickupThree->GetCenter()};
    Enemy* EnemyOne = new Enemy(overlapHandler, "EnemyOne", PatrolOne);

    Vertex PatrolTwo[3] = {PickupFour->GetCenter(), PickupFive->GetCenter(), PickupSix->GetCenter()};
    Enemy* EnemyTwo = new Enemy(overlapHandler, "EnemyTwo", PatrolTwo);

    Player* Player = ServiceProvider::GetPlayer();
    Player->move(0, 0, -30);

    Door* DoorOutside = new Door(this, 14, 0, -30, "DoorOutside");

    Door* DoorInside = new Door(this, 10, 0, -30, "DoorInside");
    DoorInside->ToggleVisible();

    House* HouseOne = new House(overlapHandler, 18, 0, -30, "House");




    objects.push_back( PickupOne );
    objects.push_back( PickupTwo );
    objects.push_back( PickupThree );

    objects.push_back( PickupFour );
    objects.push_back( PickupFive );
    objects.push_back( PickupSix );

    objects.push_back( PickupSeven );

    objects.push_back( EnemyOne );
    objects.push_back( EnemyTwo );

    objects.push_back( Player );

    objects.push_back( DoorOutside );
    objects.push_back( DoorInside );

    objects.push_back( HouseOne );

}
// SceneOne::SceneOne()
// {
//     overlapHandler = new OverlapHandler();

//     //TriangleSurface* Background = new TriangleSurface();
//     //Background->setName("Background");
//     QVector3D backgroundPos = QVector3D(-14, -14, 30);
//     float maxHeight = 30;
//     Ground* background = new Ground(backgroundPos, 0.1, maxHeight);
//     objects.push_back(background);
//     ServiceProvider::SetGround(background);

//     Pickup* PickupOne = new Pickup(overlapHandler, 7, -10, 30, "Pickup1");
//     Pickup* PickupTwo = new Pickup(overlapHandler, -7, -10, 30, "Pickup2");
//     Pickup* PickupThree = new Pickup(overlapHandler, -7, 0, 30, "Pickup3");

//     Pickup* PickupFour = new Pickup(overlapHandler, 7, 0, 30, "Pickup4");
//     Pickup* PickupFive = new Pickup(overlapHandler, 7, 10, 30, "Pickup5");
//     Pickup* PickupSix = new Pickup(overlapHandler, -7, 10, 30, "Pickup6");

//     Pickup* PickupSeven = new Pickup(overlapHandler, 18, 0, 30, "Pickup7");
//     PickupSeven->ToggleVisible();

//     Vertex PatrolOne[3] = {PickupOne->GetCenter(), PickupTwo->GetCenter(), PickupThree->GetCenter()};
//     Enemy* EnemyOne = new Enemy(overlapHandler, "EnemyOne", PatrolOne);

//     Vertex PatrolTwo[3] = {PickupFour->GetCenter(), PickupFive->GetCenter(), PickupSix->GetCenter()};
//     Enemy* EnemyTwo = new Enemy(overlapHandler, "EnemyTwo", PatrolTwo);

//     Player* Player = ServiceProvider::GetPlayer();
//     Player->move(0, 0, 30);

//     Door* DoorOutside = new Door(this, 14, 0, 30, "DoorOutside");

//     Door* DoorInside = new Door(this, 10, 0, 30, "DoorInside");
//     DoorInside->ToggleVisible();

//     House* HouseOne = new House(overlapHandler, 18, 0, 30, "House");




//     objects.push_back( PickupOne );
//     objects.push_back( PickupTwo );
//     objects.push_back( PickupThree );

//     objects.push_back( PickupFour );
//     objects.push_back( PickupFive );
//     objects.push_back( PickupSix );

//     objects.push_back( PickupSeven );

//     objects.push_back( EnemyOne );
//     objects.push_back( EnemyTwo );

//     objects.push_back( Player );

//     objects.push_back( DoorOutside );
//     objects.push_back( DoorInside );

//     objects.push_back( HouseOne );

// }

std::vector<VisualObject *> SceneOne::GetObjects()
{
    return objects;
}

IOverlapHandler *SceneOne::GetOverlapHandler()
{
    return overlapHandler;
}

void SceneOne::ToggleScene()
{
    for(auto pair : overlapHandler->GetInteractableObjects()) {
        AbstractInteractObject* entity = pair.second;
        entity->ToggleVisible();
    }
}

void SceneOne::TickScene(float deltaTime)
{
    for(VisualObject* entity : objects) {
        entity->Tick(deltaTime);
    }

    overlapHandler->Tick(deltaTime);
}
