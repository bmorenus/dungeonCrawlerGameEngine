#include "PhysicsManager.hpp"

#include <iostream>
#include <string>

#include "TinyMath.hpp"

PhysicsManager::PhysicsManager() {
    /*!
     * Singleton PhysicsManager class that manages physics processing for the game engine
     */
    std::cout << "Physics Manager Created" << std::endl;
}

PhysicsManager::PhysicsManager(PhysicsManager const&) {
}

PhysicsManager::~PhysicsManager() {
    /*!
     * Destructor Function for the PhysicsManager class
     */
    std::cout << "Physics Manager Destroyed" << std::endl;
}

PhysicsManager& PhysicsManager::GetInstance() {
    /*!
     * Returns the singleton instance of the PhysicsManager class for the game engine
     * Arguments: None
     * Returns: PhysicsManager&, the instance of the PhysicsManager class
     */
    static PhysicsManager* sInstance = new PhysicsManager();
    return *sInstance;
}

void PhysicsManager::Initialize() {
    /*!
     * Performs all initializing functions for the PhysicsManager class
     * Arguments: None
     * Returns: void
     */
}

void PhysicsManager::AddCollisionObject(GameObject* collisionObject) {
    /*!
     * Adds a game objects to the list of tracked game objects for collisions
     * Arguments: GameObject*, the game object to track for collisions
     * Returns: void
     */
    mGameObjects.push_back(collisionObject);
}

void PhysicsManager::ClearCollisionObjects() {
    /*!
     * Clears list of tracked game objects for collisions
     * Arguments: None
     * Returns: void
     */
    mGameObjects.clear();
}

int* PhysicsManager::GetCollisionDirections(GameObject* object1) {
    /*!
     * Returns an array of 4 integers that specify where, if any, collisions
     *   are taking place with the given game obejct
     * Arguments: GameObject*, the game object to check for collisions
     * Returns: int*, an array of collision indications (1 if collision, 0 if not)
     */
    int* collisions = new int[4]();

    for (GameObject* object2 : mGameObjects) {
        if (object2->GetIsDeleted()) {
            continue;
        }

        if ((object1->GetObjectType() == ObjectType::COIN && object2->GetObjectType() == ObjectType::TILE) ||
            (object1->GetObjectType() == ObjectType::COIN && object2->GetObjectType() == ObjectType::COIN)) {
            continue;
        }

        // Collision is occuring to the right of the object
        if (((object1->GetX() + (object1->GetWidth() / 2)) > (object2->GetX() - (object2->GetWidth() / 2) - mCollisionBuffer)) &&
            ((object1->GetX() + (object1->GetWidth() / 2)) < (object2->GetX() - (object2->GetWidth() / 2)))) {
            if ((object1->GetY() > (object2->GetY() - std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) - mStandoffBuffer)) &&
                (object1->GetY() < (object2->GetY() + std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) + mStandoffBuffer))) {
                collisions[0] = 1;
            };
        }

        // Collision is occuring to the left of the object
        if (((object1->GetX() - (object1->GetWidth() / 2)) > (object2->GetX() + (object2->GetWidth() / 2))) &&
            ((object1->GetX() - (object1->GetWidth() / 2)) < (object2->GetX() + (object2->GetWidth() / 2) + mCollisionBuffer))) {
            if ((object1->GetY() > (object2->GetY() - std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) - mStandoffBuffer)) &&
                (object1->GetY() < (object2->GetY() + std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) + mStandoffBuffer))) {
                collisions[1] = 1;
            }
        }

        // Collision is occuring below the object
        if (((object1->GetY() + (object1->GetHeight() / 2)) > (object2->GetY() - (object2->GetWidth() / 2) - mCollisionBuffer)) &&
            ((object1->GetY() + (object1->GetHeight() / 2)) < (object2->GetY() + (object2->GetHeight() / 2)))) {
            if ((object1->GetX() > (object2->GetX() - std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) - mStandoffBuffer)) &&
                (object1->GetX() < (object2->GetX() + std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) + mStandoffBuffer))) {
                collisions[2] = 1;
            }
        }

        // Collision is occuring above the object
        if (((object1->GetY() - (object1->GetHeight() / 2)) > (object2->GetY() + (object2->GetHeight() / 2))) &&
            ((object1->GetY() - (object1->GetHeight() / 2)) < (object2->GetY() + (object2->GetHeight() / 2) + mCollisionBuffer))) {
            if ((object1->GetX() > (object2->GetX() - std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) - mStandoffBuffer)) &&
                (object1->GetX() < (object2->GetX() + std::max(object1->GetWidth() / 2, object2->GetWidth() / 2) + mStandoffBuffer))) {
                collisions[3] = 1;
            };
        }
    }

    return collisions;
}
