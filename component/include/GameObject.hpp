#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <vector>
#include "IGraphicsEngineRenderer.hpp"

class Component;
class GameObject{
    public:
        GameObject();
        ~GameObject();

        void Update();
        void Render(SDL_Renderer* ren);
        void AddComponent(Component* c);
        void send(int message1, int message2);
    // Note: You may want to add member functions like 'Update' or 'Render'
    // Note: You may want to add member functions like "AddComponent" or "RemoveComponent"

    private:
        std::vector<Component*> list_components;
};


#endif
