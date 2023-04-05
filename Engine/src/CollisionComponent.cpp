#include "CollisionComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

CollisionComponent::CollisionComponent() {
}

CollisionComponent::~CollisionComponent() {
}

void CollisionComponent::Update(GameObject& gameObject, int frame) {
    int direction = PhysicsManager::GetInstance().GetCollisionDirection(&gameObject);
    gameObject.SetCollisionDirection(direction);
}

void CollisionComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}
