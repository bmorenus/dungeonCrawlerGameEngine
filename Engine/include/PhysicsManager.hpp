#ifndef PHYSICS_MANAGER_HPP
#define PHYSICS_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <string>
#include <vector>

#include "ControllerComponent.hpp"
#include "GameObject.hpp"
#include "TinyMath.hpp"

class PhysicsManager {
   public:
    static PhysicsManager& GetInstance();

    void Initialize();

    void AddCollisionObject(GameObject* collisionObject);

    int GetCollisionDirection(GameObject* object1);

   private:
    PhysicsManager();

    ~PhysicsManager();

    PhysicsManager(PhysicsManager const&);

    void operator=(PhysicsManager const&);

    std::vector<GameObject*> mGameObjects;
};

#endif
