#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include "Component.hpp"

class ControllerComponent : public Component{
    public:
        ControllerComponent();
        ~ControllerComponent();
        void Update(GameObject* g);
};


#endif
