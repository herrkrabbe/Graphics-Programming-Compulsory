#ifndef IPLAYER_H
#define IPLAYER_H

#include <qvector3d.h>

/*
 * Interface of functions needed by other objects to interact with
 * the player character
 */
class IPlayer {
public:
    virtual void LoseLife() = 0;
    virtual void AddPoint(int points) = 0;
    virtual int GetPoints() = 0;
    virtual QVector3D GetPosition() = 0;
    virtual float GetRadius() = 0;
    virtual void PushPlayer(QVector3D pushVector) = 0;
};

#endif // IPLAYER_H
