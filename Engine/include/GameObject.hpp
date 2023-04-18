#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

/**
 *  @file GameObject.hpp
 *  @brief Implementation of the GameObject class
 */

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
    PASSABLE_TILE,
    BLOCKABLE_TILE,
    COIN
};

/*!
 *GameObject class that represents a single game object in the game scene
 */
class GameObject {
   public:
    /*!
     * Constructor for GameObject
     */
    GameObject(SDL_Renderer* renderer, int xPos, int yPos, int width,
               int height, ObjectType type, int frame, std::string tag);

    /*!
     * Destructor for GameObject
     */
    ~GameObject();

    /*!
     * Adds an SDL_Event to be tracked and processed by the game object
     */
    void AddEvent(SDL_Event& e);

    /*!
     * Updates the state of the game object
     */
    void Update();

    /*!
     * Renders of the game object
     */
    void Render();

    /*!
     * Returns the unique speed of the game object
     */
    int GetSpeed();

    /*!
     * Sets the unique speed of the game object
     */
    void SetSpeed(int speed);

    /*!
     * Returns the x-velocity of the game object
     */
    int GetXVelocity();

    /*!
     * Sets the x-velocity of the game object
     */
    void SetXVelocity(int velocity);

    /*!
     * Returns the y-velocity of the game object
     */
    int GetYVelocity();

    /*!
     * Sets the y-velocity of the game object
     */
    void SetYVelocity(int velocity);

    /*!
     * Returns the x-position of the game object
     */
    int GetX();

    /*!
     * Sets the x-position of the game object
     */
    void SetX(int xPos);

    /*!
     * Returns the y-position of the game object
     */
    int GetY();

    /*!
     * Sets the y-position of the game object
     */
    void SetY(int yPos);

    /*!
     * Returns the width of the game object
     */
    int GetWidth();

    /*!
     * Returns the height of the game object
     */
    int GetHeight();

    /*!
     * Returns the frame of the game object
     */
    int GetFrame();

    /*!
     * Sets the frame of the game object
     */
    void SetFrame(int frame);

    /*!
     * Returns the deletion status of the game object
     */
    bool GetIsDeleted();

    /*!
     * Sets the deletion status of the game object
     */
    void SetIsDeleted(bool isDeleted);

    /*!
     * Returns the object type of the game object
     */
    ObjectType GetObjectType();

    /*!
     * Sets the object type of the game object
     */
    void SetObjectType(ObjectType objectType);

    /*!
     * Returns the frame sequence of the game object
     */
    std::string GetSequence();

    /*!
     * Sets the frame sequence of the game object
     */
    void SetSequence(std::string sequence);

    /*!
     * Returns the collision directions of the game object
     */
    int* GetCollisionDirections();

    /*!
     * Sets the collision directions of the game object
     */
    void SetCollisionDirections(int* collisionDirection);

    /*!
     * Adds a component to the game object
     */
    void AddComponent(Component* component);

    /*!
     * Returns a vector of current SDL_Events to process on the game object
     */
    std::vector<SDL_Event> GetEvents();

    /*!
     * Returns a String tag that denotes the create function of the game object
     */
    std::string GetTag();

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
