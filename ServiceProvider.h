#ifndef SERVICEPROVIDER_H
#define SERVICEPROVIDER_H
#include "Camera.h"
#include "Ground.h"
#include "Player.h"


/*
 * Singleton to get the player character
 */
class ServiceProvider
{
private:
    ServiceProvider();
    ~ServiceProvider();
    Player* player;
    Camera* camera{nullptr};
    Ground* ground{nullptr};

    static ServiceProvider* instance;


public:
    ServiceProvider(const ServiceProvider&) = delete; // rule of three
    ServiceProvider& operator=(const ServiceProvider&) = delete;

    static Player* GetPlayer() {
        return get().player;
    };

    static Camera* GetCamera() {
        return get().camera;
    }

    static Ground* GetGround() {
        return get().ground;
    }

    static bool HasCamera() {
        return nullptr!=GetCamera();
    }

    static bool HasGround() {
        return nullptr!=GetGround();
    }

    static void SetCamera(Camera* cam) {
        get().camera = cam;
    }

    static void SetGround(Ground* gro) {
        get().ground = gro;
    }

    static ServiceProvider& get() {
        if (instance == nullptr) instance = new ServiceProvider;
        return *instance;
    }

    static void destruct() {
        delete instance;
        instance = nullptr;
    }
};


#endif // SERVICEPROVIDER_H
