#include "PhysicsManager.hpp"

#include <iostream>
#include <string>

#include "TinyMath.hpp"

PhysicsManager::PhysicsManager() {
    std::cout << "Physics Manager Created" << std::endl;
}

PhysicsManager::PhysicsManager(PhysicsManager const&) {
}

PhysicsManager::~PhysicsManager() {
    std::cout << "Physics Manager Destroyed" << std::endl;
}

PhysicsManager& PhysicsManager::GetInstance() {
    static PhysicsManager* sInstance = new PhysicsManager();
    return *sInstance;
}

void PhysicsManager::Initialize() {
}

void PhysicsManager::AddCollisionObject(GameObject* collisionObject) {
    mGameObjects.push_back(collisionObject);
}

void PhysicsManager::ClearCollisionObjects() {
    mGameObjects.clear();
}

int* PhysicsManager::GetCollisionDirections(GameObject* object1) {
    int* collisions = new int[4]();

    for (GameObject* object2 : mGameObjects) {
        if (object2->GetIsDeleted()) {
            continue;
        }

        if ((object1->mObjectType == ObjectType::COIN && object2->mObjectType == ObjectType::TILE) ||
            (object1->mObjectType == ObjectType::COIN && object2->mObjectType == ObjectType::COIN)) {
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
