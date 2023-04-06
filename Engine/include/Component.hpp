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
    Component();
    virtual ~Component();
    virtual void Update(GameObject &gameObject, int frame) = 0;
    virtual void Render(GameObject &gameObject, SDL_Renderer *renderer) = 0;
};

#endif
