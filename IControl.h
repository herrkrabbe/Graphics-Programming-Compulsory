#ifndef ICONTROL_H
#define ICONTROL_H

#include <qevent.h>

struct KeyState {
    bool W{0};
    bool A{0};
    bool S{0};
    bool D{0};
};


/*
 * This class can recieve input by the player.
 */
class IControl {
public:
    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *event) = 0;
};

#endif // ICONTROL_H
