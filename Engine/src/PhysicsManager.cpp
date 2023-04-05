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

int PhysicsManager::GetCollisionDirection(GameObject* object1) {
    for (GameObject* object2 : mGameObjects) {
        if (((object1->GetX() + object1->GetWidth()) > (object2->GetX() - 5)) &&
            ((object1->GetX() + object1->GetWidth()) < (object2->GetX() + 5))) {
            std::cout << "cond 1" << std::endl;
            if ((object1->GetY() > (object2->GetY() - object2->GetHeight())) &&
                (object1->GetY() < (object2->GetY() + object2->GetHeight()))) {
                return 1;
            };
        }

        if ((object1->GetX() > (object2->GetX() + object2->GetWidth() - 5)) &&
            (object1->GetX() < (object2->GetX() + object2->GetWidth()) + 5)) {
            std::cout << "cond 2" << std::endl;
            if ((object1->GetY() > (object2->GetY() - object2->GetHeight())) &&
                (object1->GetY() < (object2->GetY() + object2->GetHeight()))) {
                return 2;
            }
        }

        if (((object1->GetY() + object1->GetHeight()) > (object2->GetY() - 5)) &&
            (object1->GetY() + object1->GetHeight()) < (object2->GetY() + 5)) {
            std::cout << "cond 3" << std::endl;
            if ((object1->GetX() > (object2->GetX() - object2->GetWidth())) &&
                (object1->GetX() < (object2->GetX() + object2->GetWidth()))) {
                return 3;
            }
        }

        if (((object1->GetY() - 5) < (object2->GetY() + object2->GetHeight())) &&
            ((object1->GetY() + 5) > (object2->GetY() + object2->GetHeight()))) {
            std::cout << "cond 4" << std::endl;
            if ((object1->GetX() > (object2->GetX() - object2->GetWidth())) &&
                (object1->GetX() < (object2->GetX() + object2->GetWidth()))) {
                return 4;
            };
        }
    }
    return 0;
}
