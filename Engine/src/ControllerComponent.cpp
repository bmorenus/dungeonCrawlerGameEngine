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
        std::cout << e.key.keysym.sym << std::endl;
        if (e.type == SDL_KEYDOWN) {
            std::cout << "Key Down" << std::endl;
            if (e.key.keysym.sym == SDLK_a) {
                std::cout << "Moving Left" << std::endl;
                if (gameObject.GetVelocity() > 0) {
                    gameObject.SetVelocity(gameObject.GetVelocity() * -ACCELERATION);
                }
            }
            if (e.key.keysym.sym == SDLK_d) {
                std::cout << "Moving Right" << std::endl;
                if (gameObject.GetVelocity() < 0) {
                    gameObject.SetVelocity(gameObject.GetVelocity() * -ACCELERATION);
                }
            }
        }
    }
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer){
}
