#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <SDL.h>
#include "ControllerComponent.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "Component.hpp"

class GameObject{
    public:
        GameObject(SDL_Renderer* renderer);
        ~GameObject();

        void AddEvent(SDL_Event e);
        void Update(int frame);
        void Render(SDL_Renderer* renderer);

        int GetVelocity();
        void SetVelocity(int velocity);

        int GetX();
        void SetX(int x);

        SpriteComponent GetSpriteComponent();
        void AddComponent(Component* component);
        std::vector<SDL_Event> GetEvents();
        SDL_Renderer* GetRenderer();
    
    private:
        int m_velocity;
        int m_x;
        int frame;
        SDL_Renderer* m_renderer;
        std::vector<SDL_Event> m_events;
        std::vector<Component*> m_components;
        ControllerComponent m_controllerComponent;
        TransformComponent m_transformComponent;
        SpriteComponent m_spriteComponent;
};


#endif
