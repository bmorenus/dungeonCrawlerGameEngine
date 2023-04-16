#include "ControllerComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

ControllerComponent::ControllerComponent() {
    /*!
     * Constructor for the ControllerComponent that sets the behavior of
     *   components when an event input occurs by the user
     *
     * Arguments: None
     */
}

ControllerComponent::~ControllerComponent() {
    /*!
     * Destructor for the ControllerComponent
     */
}

void ControllerComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
    HandleEvents(gameObject);
    HandleMovement(gameObject);
}

void ControllerComponent::HandleEvents(GameObject& gameObject) {
    /*!
     * Handles the non-movement events found added to the mEvents vector of
     *   the game object
     *
     * Arguments: GameObject& gameObject, the game object to handle events for
     * Returns: void
     */
    std::vector<SDL_Event> events = gameObject.GetEvents();
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
    ResetEvents(gameObject);
}

void ControllerComponent::HandleMovement(GameObject& gameObject) {
    /*!
     * Handles the movement events found added to the mEvents vector of
     *   the game object
     *
     * Arguments: GameObject& gameObject, the game object to handle movements for
     * Returns: void
     */
    const Uint8* currentKey = SDL_GetKeyboardState(NULL);
    int* collisionDirection = gameObject.GetCollisionDirections();

    int xVelocity = 0;
    int yVelocity = 0;

    if (currentKey[SDL_SCANCODE_D] && collisionDirection[0] != 1) {
        gameObject.SetSequence("right_walking");
        xVelocity = gameObject.GetSpeed();
    } else if (currentKey[SDL_SCANCODE_A] && collisionDirection[1] != 1) {
        gameObject.SetSequence("left_walking");
        xVelocity = -gameObject.GetSpeed();
    } else if (currentKey[SDL_SCANCODE_S] && collisionDirection[2] != 1) {
        gameObject.SetSequence("forward_walking");
        yVelocity = gameObject.GetSpeed();
    } else if (currentKey[SDL_SCANCODE_W] && collisionDirection[3] != 1) {
        gameObject.SetSequence("backward_walking");
        yVelocity = -gameObject.GetSpeed();
    } else {
        gameObject.SetXVelocity(0);
        gameObject.SetYVelocity(0);
    }

    gameObject.SetXVelocity(xVelocity);
    gameObject.SetYVelocity(yVelocity);
}

void ControllerComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
}

void ControllerComponent::ResetEvents(GameObject& gameObject) {
    /*!
     * Clears events in the mEvents vector of the game object
     *
     * Arguments: GameObject& gameObject, the game object to reset events of
     * Returns: void
     */
    gameObject.GetEvents().clear();
}
