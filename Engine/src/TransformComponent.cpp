#include <iostream>

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "GameObject.hpp"

TransformComponent::TransformComponent(){
}

TransformComponent::~TransformComponent(){
}

void TransformComponent::Update(GameObject& gameObject, int frame){
    int gameObjectX = gameObject.GetX();
    int gameObjectVelocity =  gameObject.GetVelocity();
    gameObject.SetX(gameObjectX + gameObjectVelocity);
}

void TransformComponent::Render(GameObject& gameObject, SDL_Renderer* renderer){
}