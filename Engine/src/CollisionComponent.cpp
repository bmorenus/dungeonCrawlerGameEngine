#include "CollisionComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

CollisionComponent::CollisionComponent() {
    /*!
     * Constructor for the CollisionComponent that sets the behavior of
     *   collidable objects when they are collided with
     *
     * Arguments: None
     */
}

CollisionComponent::~CollisionComponent() {
    /*!
     * Destructor for the CoinCollisionComponent
     */
}

void CollisionComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
    int* collisions = PhysicsManager::GetInstance().GetCollisionDirections(&gameObject);
    gameObject.SetCollisionDirections(collisions);
}

void CollisionComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
}
