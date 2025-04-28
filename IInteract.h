#ifndef IINTERACT_H
#define IINTERACT_H

#include "IPlayer.h"
/*
 * Interface responsible for what happens when an object is interacted with.
 * The class is not responsible for checking wheter a object should be interacted with.
 */
class IInteract {
public:
    virtual void Interact(IPlayer* interactor) = 0;
};

#endif // IINTERACT_H
