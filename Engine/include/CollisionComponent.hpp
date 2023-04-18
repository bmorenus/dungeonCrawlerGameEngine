#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"

class GameObject;

/*!
 * Collision component that defines the behavior of default objects when colliding
 */
class CollisionComponent : public Component {
   public:
    /*!
     * Constructor for the CollisionComponent that sets the behavior of stoppable objects when they collide
     */
    CollisionComponent();

    /*!
     * Destructor for the CollisionComponent
     */
    ~CollisionComponent();

    /*!
     * Updates the provided game object
     */
    void Update(GameObject& gameObject) override;

    /*!
     * Renders the provided game object
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;
};

#endif
