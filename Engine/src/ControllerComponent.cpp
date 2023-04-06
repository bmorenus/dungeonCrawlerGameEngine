#include "ControllerComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

ControllerComponent::ControllerComponent() {
}

ControllerComponent::~ControllerComponent() {
}

void ControllerComponent::Update(GameObject& gameObject) {
    std::vector<SDL_Event> events = gameObject.GetEvents();
    int speed = gameObject.GetSpeed();

    const Uint8* currentKey = SDL_GetKeyboardState(NULL);
    int* collisionDirection = gameObject.GetCollisionDirections();

    for (SDL_Event e : events) {
        if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_d:
                    gameObject.SetSequence("right_standing");
                    break;
                case SDLK_a:
                    gameObject.SetSequence("left_standing");
                    break;
                case SDLK_w:
                    gameObject.SetSequence("backward_standing");
                    break;
                case SDLK_s:
                    gameObject.SetSequence("forward_standing");
                    break;
                default:
                    break;
            }
        }
    }

    if (currentKey[SDL_SCANCODE_D]) {
        gameObject.SetSequence("right_walking");
        if (collisionDirection[0] != 1) {
            gameObject.SetXVelocity(speed);
            gameObject.SetYVelocity(0);
        } else {
            gameObject.SetXVelocity(0);
        }
    } else if (currentKey[SDL_SCANCODE_A]) {
        gameObject.SetSequence("left_walking");
        if (collisionDirection[1] != 1) {
            gameObject.SetXVelocity(-speed);
            gameObject.SetYVelocity(0);
        } else {
            gameObject.SetXVelocity(0);
        }
    } else if (currentKey[SDL_SCANCODE_S]) {
        gameObject.SetSequence("forward_walking");
        if (collisionDirection[2] != 1) {
            gameObject.SetYVelocity(speed);
            gameObject.SetXVelocity(0);
        } else {
            gameObject.SetYVelocity(0);
        }
    } else if (currentKey[SDL_SCANCODE_W]) {
        gameObject.SetSequence("backward_walking");
        if (collisionDirection[3] != 1) {
            gameObject.SetYVelocity(-speed);
            gameObject.SetXVelocity(0);
        } else {
            gameObject.SetYVelocity(0);
        }
    } else {
        gameObject.SetXVelocity(0);
        gameObject.SetYVelocity(0);
    }

    ResetEvents(gameObject);
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
}

void ControllerComponent::ResetEvents(GameObject& gameObject) {
    gameObject.GetEvents().clear();
}
