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

/*!
 * Singleton PhysicsManager class that manages physics processing for the game engine
 */
class PhysicsManager {
   public:
    /*!
     * Returns the singleton instance of the PhysicsManager class for the game engine
     */
    static PhysicsManager& GetInstance();

    /*!
     * Performs all initializing functions for the PhysicsManager class
     */
    void Initialize();

    /*!
     * Adds a game objects to the list of tracked game objects for collisions
     */
    void AddCollisionObject(GameObject* collisionObject);

    /*!
     * Returns an array of 4 integers that specify where, if any, collisions are taking place with the given game obejct
     */
    int* GetCollisionDirections(GameObject* object1);

    /*!
     * Clears list of tracked game objects for collisions
     */
    void ClearCollisionObjects();

   private:
    /*!
     * Constructor Function for the PhysicsManager class
     */
    PhysicsManager();

    /*!
     * Destructor Function for the PhysicsManager class
     */
    ~PhysicsManager();

    PhysicsManager(PhysicsManager const&);

    void operator=(PhysicsManager const&);

    std::vector<GameObject*> mGameObjects;

    int mCollisionBuffer = 4;
    int mStandoffBuffer = 17;
};

#endif
