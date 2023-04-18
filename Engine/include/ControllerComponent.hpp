#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"

class GameObject;

class ControllerComponent : public Component {
   public:
    /*!
     * Constructor for the ControllerComponent that sets the behavior of components when an event input occurs by the user
     */
    ControllerComponent();

    /*!
     * Destructor for the ControllerComponent
     */
    ~ControllerComponent();

    /*!
     * Updates the provided game object
     */
    void Update(GameObject& gameObject) override;

    /*!
     * Renders the provided game object
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    /*!
     * Clears events in the mEvents vector of the game object
     */
    void ResetEvents(GameObject& gameObject);

    /*!
     * Handles the non-movement events found added to the mEvents vector of the game object
     */
    void HandleEvents(GameObject& gameObject);

    /*!
     * Handles the movement events found added to the mEvents vector of the game object
     */
    void HandleMovement(GameObject& gameObject);
};

#endif
