#include "GameObject.hpp"

#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int xPos, int yPos, int frame) {
    mXPos = xPos;
    mYPos = yPos;
    mFrame = frame;
    mVelocity = 5;
    mRenderer = renderer;
}

GameObject::~GameObject() {
    // Make components a shared pointer
}

void GameObject::AddEvent(SDL_Event& e) {
    mEvents.push_back(e);
}
void GameObject::Update(int frame) {
    for (int i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Update(*this, frame);
    }
}
void GameObject::Render(SDL_Renderer* renderer) {
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
    return mXPos;
}

void GameObject::SetX(int xPos) {
    mXPos = xPos;
}

int GameObject::GetY() {
    return mYPos;
}

void GameObject::SetY(int yPos) {
    mYPos = yPos;
}

int GameObject::GetFrame() {
    return mFrame;
}

void GameObject::SetFrame(int frame) {
    mFrame = frame;
}

void GameObject::AddComponent(Component* component) {
    mComponents.push_back(component);
}

std::vector<SDL_Event> GameObject::GetEvents() {
    return mEvents;
}