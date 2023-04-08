#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"

class GameObject;

class CollisionComponent : public Component {
   public:
    CollisionComponent();
    ~CollisionComponent();
    void Update(GameObject& gameObject) override;
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;
};

#endif
