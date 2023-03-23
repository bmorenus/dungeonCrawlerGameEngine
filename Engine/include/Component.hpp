#ifndef COMPONENT_HPP 
#define COMPONENT_HPP

#include <SDL.h>

class GameObject;

class Component {
    public:
        Component();
        virtual ~Component();
        virtual void Update(GameObject& gameObject, int frame) = 0;
        virtual void Render(GameObject& gameObject, SDL_Renderer* renderer) = 0;
};


#endif
