#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

class GameObject;

class Component {
   public:
    /*!
     * Constructor for the Component
     */
    Component();
    /*!
     * Destructor for the Component
     */
    virtual ~Component();

    /*!
     * Updates the provided game object
     */
    virtual void Update(GameObject& gameObject) = 0;

    /*!
     * Renders the provided game object
     */
    virtual void Render(GameObject& gameObject, SDL_Renderer* renderer) = 0;
};

#endif
