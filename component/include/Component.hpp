#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"
#include "GameObject.hpp"
#include <string>
#include <array>
#include <iostream>

class Component{
    public:
        Component();
        ~Component();
        virtual void Update(GameObject* g);
        virtual void Render(SDL_Renderer* ren);
        virtual void receive(int message1, int message2);

};


#endif
