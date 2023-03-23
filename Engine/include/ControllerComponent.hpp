#ifndef CONTROLLERCOMPONENT_HPP 
#define CONTROLLERCOMPONENT_HPP

#include "Component.hpp"
#include <SDL.h>

class GameObject;

class ControllerComponent : public Component {
    public:
        ControllerComponent();
        ~ControllerComponent();
        void Update(GameObject& gameObject, int frame) override;
        void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

    private:
        const float ACCELERATION = 1;
};


#endif
