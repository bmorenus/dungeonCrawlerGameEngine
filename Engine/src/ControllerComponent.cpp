#include "ControllerComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

ControllerComponent::ControllerComponent() {
}

ControllerComponent::~ControllerComponent() {
}

void ControllerComponent::Update(GameObject& gameObject, int frame) {
    std::vector<SDL_Event> events = gameObject.GetEvents();

    const Uint8* currentKey = SDL_GetKeyboardState(NULL);
    int collisionDirection = gameObject.GetCollisionDirection();

    if (currentKey[SDL_SCANCODE_D]) {
        if (collisionDirection != 1) {
            if (gameObject.GetVelocity() <= 0) {
                gameObject.SetVelocity(gameObject.GetVelocity() + 5);
            }
        } else {
            if (gameObject.GetVelocity() > 0) {
                gameObject.SetVelocity(gameObject.GetVelocity() - 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_D]) {
        if (gameObject.GetVelocity() > 0) {
            gameObject.SetVelocity(gameObject.GetVelocity() - 5);
        }
    }
    if (currentKey[SDL_SCANCODE_A]) {
        if (collisionDirection != 2) {
            if (gameObject.GetVelocity() >= 0) {
                gameObject.SetVelocity(gameObject.GetVelocity() - 5);
            }
        } else {
            if (gameObject.GetVelocity() < 0) {
                gameObject.SetVelocity(gameObject.GetVelocity() + 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_A]) {
        if (gameObject.GetVelocity() < 0) {
            gameObject.SetVelocity(gameObject.GetVelocity() + 5);
        }
    }

    ResetEvents(gameObject);
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}

void ControllerComponent::ResetEvents(GameObject& gameObject) {
    gameObject.GetEvents().clear();
}
