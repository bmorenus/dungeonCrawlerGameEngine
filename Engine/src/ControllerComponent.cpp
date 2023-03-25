#include <iostream>

#include "ControllerComponent.hpp"
#include "GameObject.hpp"

ControllerComponent::ControllerComponent(){
}

ControllerComponent::~ControllerComponent(){
}

void ControllerComponent::Update(GameObject& gameObject, int frame){
    std::vector<SDL_Event> events = gameObject.GetEvents();

    for (SDL_Event e : events) {
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_a) {
                if (gameObject.GetVelocity() > 0) {
                    gameObject.SetVelocity(gameObject.GetVelocity() * -ACCELERATION);
                }
            }
            if (e.key.keysym.sym == SDLK_d) {
                if (gameObject.GetVelocity() < 0) {
                    gameObject.SetVelocity(gameObject.GetVelocity() * -ACCELERATION);
                }
            }
        }
    }
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer){
}
