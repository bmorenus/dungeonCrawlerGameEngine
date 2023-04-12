#ifndef COINCOLLISIONCOMPONENT_HPP
#define COINCOLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"

class GameObject;

class CoinCollisionComponent : public Component {
   public:
    CoinCollisionComponent();
    ~CoinCollisionComponent();
    void Update(GameObject& gameObject) override;
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;
};

#endif
