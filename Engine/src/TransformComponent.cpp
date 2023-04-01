#include "TransformComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "SpriteComponent.hpp"

TransformComponent::TransformComponent() {
}

TransformComponent::~TransformComponent() {
}

void TransformComponent::Update(GameObject& gameObject, int frame) {
    int gameObjectX = gameObject.GetX();
    int gameObjectVelocity = gameObject.GetVelocity();
    gameObject.SetX(gameObjectX + gameObjectVelocity);
}

void TransformComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}