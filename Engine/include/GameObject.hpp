#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <vector>

#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

class GameObject {
   public:
    GameObject(SDL_Renderer* renderer);
    ~GameObject();

    void AddEvent(SDL_Event& e);
    void Update(int frame);
    void Render(SDL_Renderer* renderer, SDL_Texture* texture);

    int GetVelocity();
    void SetVelocity(int velocity);

    int GetX();
    void SetX(int x);

    void AddComponent(Component* component);
    std::vector<SDL_Event> GetEvents();

   private:
    int mVelocity;
    int mX;
    int frame;
    SDL_Renderer* mRenderer;
    std::vector<SDL_Event> mEvents;
    std::vector<Component*> mComponents;
    ControllerComponent mControllerComponent;
    TransformComponent mTransformComponent;
};

#endif
