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
            if (gameObject.GetXVelocity() <= 0) {
                gameObject.SetXVelocity(gameObject.GetXVelocity() + 5);
            }
        } else {
            if (gameObject.GetXVelocity() > 0) {
                gameObject.SetXVelocity(gameObject.GetXVelocity() - 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_D]) {
        if (gameObject.GetXVelocity() > 0) {
            gameObject.SetXVelocity(gameObject.GetXVelocity() - 5);
        }
    }
    if (currentKey[SDL_SCANCODE_A]) {
        if (collisionDirection[1] != 1) {
            if (gameObject.GetXVelocity() >= 0) {
                gameObject.SetXVelocity(gameObject.GetXVelocity() - 5);
            }
        } else {
            if (gameObject.GetXVelocity() < 0) {
                gameObject.SetXVelocity(gameObject.GetXVelocity() + 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_A]) {
        if (gameObject.GetXVelocity() < 0) {
            gameObject.SetXVelocity(gameObject.GetXVelocity() + 5);
        }
    }
    if (currentKey[SDL_SCANCODE_S]) {
        if (collisionDirection[2] != 1) {
            if (gameObject.GetYVelocity() <= 0) {
                gameObject.SetYVelocity(gameObject.GetYVelocity() + 5);
            }
        } else {
            if (gameObject.GetYVelocity() > 0) {
                gameObject.SetYVelocity(gameObject.GetYVelocity() - 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_S]) {
        if (gameObject.GetYVelocity() > 0) {
            gameObject.SetYVelocity(gameObject.GetYVelocity() - 5);
        }
    }
    if (currentKey[SDL_SCANCODE_W]) {
        if (collisionDirection[3] != 1) {
            if (gameObject.GetYVelocity() >= 0) {
                gameObject.SetYVelocity(gameObject.GetYVelocity() - 5);
            }
        } else {
            if (gameObject.GetYVelocity() < 0) {
                gameObject.SetYVelocity(gameObject.GetYVelocity() + 5);
            }
        }
    }
    if (!currentKey[SDL_SCANCODE_W]) {
        if (gameObject.GetYVelocity() < 0) {
            gameObject.SetYVelocity(gameObject.GetYVelocity() + 5);
        }
    }

    ResetEvents(gameObject);
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}

void ControllerComponent::ResetEvents(GameObject& gameObject) {
    gameObject.GetEvents().clear();
}
