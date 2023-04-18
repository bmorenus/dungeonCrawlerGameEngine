#ifndef COINCOLLISIONCOMPONENT_HPP
#define COINCOLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"

class GameObject;

/*!
 * Collision component that defines the behavior of coins when colliding
 */
class CoinCollisionComponent : public Component {
   public:
    /*!
     * Constructor for the CoinCollisionComponent that sets the behavior of coins when they are collided with
     */
    CoinCollisionComponent();

    /*!
     * Destructor for the CoinCollisionComponent
     */
    ~CoinCollisionComponent();

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
