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
    ControllerComponent();
    ~ControllerComponent();
    void Update(GameObject& gameObject) override;
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    void ResetEvents(GameObject& gameObject);

    const float ACCELERATION = 1;
};

#endif
