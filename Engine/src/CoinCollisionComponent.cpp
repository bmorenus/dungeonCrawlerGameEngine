#include "CoinCollisionComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

CoinCollisionComponent::CoinCollisionComponent() {
}

CoinCollisionComponent::~CoinCollisionComponent() {
}

void CoinCollisionComponent::Update(GameObject& gameObject) {
    int* collisions = PhysicsManager::GetInstance().GetCollisionDirections(&gameObject);
    for (int i = 0; i < 4; i++) {
        if (collisions[i] == 1)
            gameObject.SetIsDeleted(true);
    }
    gameObject.SetCollisionDirections(collisions);
}

void CoinCollisionComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}
