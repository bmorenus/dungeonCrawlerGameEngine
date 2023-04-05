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
    int gameObjectY = gameObject.GetY();

    int gameObjectXVelocity = gameObject.GetXVelocity();
    int gameObjectYVelocity = gameObject.GetYVelocity();

    gameObject.SetX(gameObjectX + gameObjectXVelocity);
    gameObject.SetY(gameObjectY + gameObjectYVelocity);
}

void TransformComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}