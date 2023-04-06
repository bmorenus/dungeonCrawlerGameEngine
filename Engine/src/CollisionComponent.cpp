#include "CollisionComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

CollisionComponent::CollisionComponent() {
}

CollisionComponent::~CollisionComponent() {
}

void CollisionComponent::Update(GameObject& gameObject, int frame) {
    int* collisions = PhysicsManager::GetInstance().GetCollisionDirections(&gameObject);
    gameObject.SetCollisionDirections(collisions);
}

void CollisionComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}
