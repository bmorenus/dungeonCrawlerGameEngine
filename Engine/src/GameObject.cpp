#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer){
    m_x = 20;
    m_velocity = 5;
    m_renderer = renderer;
}

GameObject::~GameObject(){
    for (int i = 0; i < m_components.size(); i++) {
        delete (m_components[i]);
    }
}

void GameObject::AddEvent(SDL_Event e){
    m_events.push_back(e);
}
void GameObject::Update(int frame){
    for (int i = 0; i < m_components.size(); i++) {
        m_components[i]->Update(*this, frame);
    }
}
void GameObject::Render(SDL_Renderer* renderer){
    for (int i = 0; i < m_components.size(); i++) {
        m_components[i]->Render(*this, renderer);
    }
}

int GameObject::GetVelocity() {
    return m_velocity;
}

void GameObject::SetVelocity(int velocity) {
    m_velocity = velocity;
}

int GameObject::GetX() {
    return m_x;
}

void GameObject::SetX(int x) {
    m_x = x; 
}

SpriteComponent GameObject::GetSpriteComponent() {
    return m_spriteComponent;
}

void GameObject::AddComponent(Component* component) {
    m_components.push_back(component);
}

std::vector<SDL_Event> GameObject::GetEvents() {
    return m_events;
}