#include "CoinCollisionComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

CoinCollisionComponent::CoinCollisionComponent() {
    /*!
     * Constructor for the CoinCollisionComponent that sets the behavior of
     *   coins when they are collided with
     *
     * Arguments: None
     */
}

CoinCollisionComponent::~CoinCollisionComponent() {
    /*!
     * Destructor for the CoinCollisionComponent
     */
}

void CoinCollisionComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
    int* collisions = PhysicsManager::GetInstance().GetCollisionDirections(&gameObject);
    for (int i = 0; i < 4; i++) {
        if (collisions[i] == 1)
            gameObject.SetIsDeleted(true);
    }
    gameObject.SetCollisionDirections(collisions);
}

void CoinCollisionComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
}
