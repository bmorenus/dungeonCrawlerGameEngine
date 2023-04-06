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
    int* collisionDirection = gameObject.GetCollisionDirections();

    if (currentKey[SDL_SCANCODE_D]) {
        if (collisionDirection[0] != 1) {
            gameObject.SetXVelocity(2);
        } else {
            gameObject.SetXVelocity(0);
        }
    } else if (currentKey[SDL_SCANCODE_A]) {
        if (collisionDirection[1] != 1) {
            gameObject.SetXVelocity(-2);
        } else {
            gameObject.SetXVelocity(0);
        }
    } else {
        gameObject.SetXVelocity(0);
    };

    if (currentKey[SDL_SCANCODE_S]) {
        if (collisionDirection[2] != 1) {
            gameObject.SetYVelocity(2);
        } else {
            gameObject.SetYVelocity(0);
        }
    } else if (currentKey[SDL_SCANCODE_W]) {
        if (collisionDirection[3] != 1) {
            gameObject.SetYVelocity(-2);
        } else {
            gameObject.SetYVelocity(0);
        }
    } else {
        gameObject.SetYVelocity(0);
    }

    ResetEvents(gameObject);
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}

void ControllerComponent::ResetEvents(GameObject& gameObject) {
    gameObject.GetEvents().clear();
}
