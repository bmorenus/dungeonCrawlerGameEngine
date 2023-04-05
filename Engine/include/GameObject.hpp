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
    GameObject(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, int frame);
    ~GameObject();

    void AddEvent(SDL_Event& e);
    void Update(int frame);
    void Render(SDL_Renderer* renderer);

    int GetXVelocity();
    void SetXVelocity(int velocity);

    int GetYVelocity();
    void SetYVelocity(int velocity);

    int GetX();
    void SetX(int xPos);

    int GetY();
    void SetY(int yPos);

    int GetWidth();
    int GetHeight();

    int GetFrame();
    void SetFrame(int frame);

    int GetCollisionDirection();
    void SetCollisionDirection(int collisionDirection);

    void AddComponent(Component* component);
    std::vector<SDL_Event> GetEvents();

   private:
    int mXVelocity;
    int mYVelocity;
    int mXPos;
    int mYPos;
    int mWidth;
    int mHeight;
    int mFrame;
    int mCollisionDirection;

    SDL_Renderer* mRenderer;
    std::vector<SDL_Event> mEvents;
    std::vector<Component*> mComponents;
    ControllerComponent mControllerComponent;
    TransformComponent mTransformComponent;
};

#endif
