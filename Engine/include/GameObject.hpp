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
        int mVelocity;
        int mX;
        int frame;
        SDL_Renderer* mRenderer;
        std::vector<SDL_Event> mEvents;
        std::vector<Component*> mComponents;
        ControllerComponent mControllerComponent;
        TransformComponent mTransformComponent;
        SpriteComponent mSpriteComponent;
};


#endif
