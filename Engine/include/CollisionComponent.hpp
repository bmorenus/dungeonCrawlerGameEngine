#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include <SDL.h>

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
