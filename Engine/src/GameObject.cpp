#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer){
    mX = 20;
    mVelocity = 5;
    mRenderer = renderer;
}

GameObject::~GameObject(){
    for (int i = 0; i < mComponents.size(); i++) {
        delete (mComponents[i]);
    }
}

void GameObject::AddEvent(SDL_Event& e){
    mEvents.push_back(e);
}
void GameObject::Update(int frame){
    for (int i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Update(*this, frame);
    }
}
void GameObject::Render(SDL_Renderer* renderer){
    for (int i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Render(*this, renderer);
    }
}

int GameObject::GetVelocity() {
    return mVelocity;
}

void GameObject::SetVelocity(int velocity) {
    mVelocity = velocity;
}

int GameObject::GetX() {
    return mX;
}

void GameObject::SetX(int x) {
    mX = x; 
}

SpriteComponent GameObject::GetSpriteComponent() {
    return mSpriteComponent;
}

void GameObject::AddComponent(Component* component) {
    mComponents.push_back(component);
}

std::vector<SDL_Event> GameObject::GetEvents() {
    return mEvents;
}