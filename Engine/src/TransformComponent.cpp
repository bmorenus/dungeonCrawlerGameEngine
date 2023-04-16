#include "TransformComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "SpriteComponent.hpp"

TransformComponent::TransformComponent() {
    /*!
     * Constructor for the TransformComponent that changes the positional state
     *   of the game object to which it is attached
     *
     * Arguments: None
     */
}

TransformComponent::~TransformComponent() {
    /*!
     * Destructor for the TransformComponent
     */
}

void TransformComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object by setting its x and y positions in
     *   accordance with its current x and y velocities
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
    int gameObjectX = gameObject.GetX();
    int gameObjectY = gameObject.GetY();

    int gameObjectXVelocity = gameObject.GetXVelocity();
    int gameObjectYVelocity = gameObject.GetYVelocity();

    gameObject.SetX(gameObjectX + gameObjectXVelocity);
    gameObject.SetY(gameObjectY + gameObjectYVelocity);
}

void TransformComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
}