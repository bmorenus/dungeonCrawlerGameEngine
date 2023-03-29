#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include <SDL.h>

#include "Component.hpp"

class GameObject;

class ControllerComponent : public Component {
   public:
    ControllerComponent();
    ~ControllerComponent();
    void Update(GameObject& gameObject, int frame) override;
    void Render(GameObject& gameObject, SDL_Renderer* renderer, SDL_Texture* texture) override;

   private:
    const float ACCELERATION = 1;
};

#endif
