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

enum ObjectType {
    DEFAULT,
    TILE,
    COIN
};

class GameObject {
   public:
    GameObject(SDL_Renderer* renderer, int xPos, int yPos, int width,
               int height, ObjectType type, int frame, std::string tag);

    ~GameObject();

    void AddEvent(SDL_Event& e);
    void Update();
    void Render();

    int GetSpeed();
    void SetSpeed(int speed);

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

    bool GetIsDeleted();
    void SetIsDeleted(bool isDeleted);

    ObjectType GetObjectType();
    void SetObjectType(ObjectType objectType);

    std::string GetSequence();
    void SetSequence(std::string sequence);

    int* GetCollisionDirections();
    void SetCollisionDirections(int* collisionDirection);

    void AddComponent(Component* component);
    std::vector<SDL_Event> GetEvents();

    std::string GetTag();

    std::vector<Component*> GetComponents();

    bool isRender = true;

   private:
    int mXVelocity;
    int mYVelocity;
    int mSpeed;
    int mXPos;
    int mYPos;
    int mWidth;
    int mHeight;
    int mFrame;
    std::string mSequence = "forward_standing";
    int* mCollisionDirection;
    bool mIsDeleted = false;
    std::string mTag = "";
    ObjectType mObjectType = ObjectType::DEFAULT;

    SDL_Renderer* mRenderer;
    std::vector<SDL_Event> mEvents;
    std::vector<Component*> mComponents;
};

#endif
