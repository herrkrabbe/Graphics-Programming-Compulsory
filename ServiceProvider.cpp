#include "ServiceProvider.h"


ServiceProvider::ServiceProvider()
{
    player = new Player();
}

ServiceProvider::~ServiceProvider()
{
    delete player;
}

