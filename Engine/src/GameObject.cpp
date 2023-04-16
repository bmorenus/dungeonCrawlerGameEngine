#include "GameObject.hpp"

#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int xPos, int yPos, int width,
                       int height, ObjectType type, int frame, std::string tag) {
    /*!
     * GameObject class that represents a single game object in the game scene

     * mXPos: int, the x position of the game object
     * mYPos: int, the y position of the game object
     * mWidth: int, the width of the game object
     * mHeight: int, the height of the game object
     * mFrame: int, the sprite frame number currently used by game object
     * mXVelocity: int, the current x velocity of the game object
     * mYVelocity: int, the current y velocity of the game object
     * mSpeed: int, the speed at which the game object can move in all directions
     * mCollisionDirection: int[4], array containing current collisions with
     *   the game object
     * mRenderer:, SDL_Renderer*, the renderer used to render the game object
     * mObjectType: ObjectType, the type of object the game object is
     * mTag: String, tag to identify the function used to build the game object
     */
    mXPos = xPos;
    mYPos = yPos;
    mWidth = width;
    mHeight = height;
    mFrame = frame;
    mXVelocity = 0;
    mYVelocity = 0;
    mSpeed = 1;
    mCollisionDirection = new int[4]();
    mRenderer = renderer;
    mObjectType = type;
    mTag = tag;
}

GameObject::~GameObject() {
    /*!
     * Destructor for GameObject
     */
    delete mCollisionDirection;
}

void GameObject::AddEvent(SDL_Event& e) {
    /*!
     * Adds an SDL_Event to be tracked and processed by the game object
     *
     * Arguments: SDL_Event, e: the event to add to the array
     * Returns: void
     */
    mEvents.push_back(e);
}

void GameObject::Update() {
    /*!
     * Updates the state of the game object
     *
     * Arguments: None
     * Returns: void
     */
    for (int i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Update(*this);
    }
}

void GameObject::Render() {
    /*!
     * Renders of the game object
     *
     * Arguments: None
     * Returns: void
     */
    for (int i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Render(*this, mRenderer);
    }
}

int GameObject::GetXVelocity() {
    /*!
     * Returns the x-velocity of the game object
     *
     * Arguments: None
     * Returns: int, the x-velocity of the game object
     */
    return mXVelocity;
}

void GameObject::SetXVelocity(int velocity) {
    /*!
     * Sets the x-velocity of the game object
     *
     * Arguments: int, the x-velocity of the game object
     * Returns: void
     */
    mXVelocity = velocity;
}

int GameObject::GetYVelocity() {
    /*!
     * Returns the y-velocity of the game object
     *
     * Arguments: None
     * Returns: int, the y-velocity of the game object
     */
    return mYVelocity;
}

void GameObject::SetYVelocity(int velocity) {
    /*!
     * Sets the y-velocity of the game object
     *
     * Arguments: int, the y-velocity of the game object
     * Returns: void
     */
    mYVelocity = velocity;
}

int* GameObject::GetCollisionDirections() {
    /*!
     * Returns the collision directions of the game object
     *
     * Arguments: None
     * Returns: int*, the current collision directions of the game object
     */
    return mCollisionDirection;
}

void GameObject::SetCollisionDirections(int* collisionDirection) {
    /*!
     * Sets the collision directions of the game object
     *
     * Arguments: int*, the current collision directions of the game object
     * Returns: void
     */
    std::copy(collisionDirection, collisionDirection + 4, mCollisionDirection);
    delete collisionDirection;
}

int GameObject::GetX() {
    /*!
     * Returns the x-position of the game object
     *
     * Arguments: None
     * Returns: int, the x-position of the game object
     */
    return mXPos;
}

void GameObject::SetX(int xPos) {
    /*!
     * Sets the x-position of the game object
     *
     * Arguments: int, the x-position of the game object
     * Returns: void
     */
    mXPos = xPos;
}

int GameObject::GetY() {
    /*!
     * Returns the y-position of the game object
     *
     * Arguments: None
     * Returns: int, the y-position of the game object
     */
    return mYPos;
}

void GameObject::SetY(int yPos) {
    /*!
     * Sets the y-position of the game object
     *
     * Arguments: int, the y-position of the game object
     * Returns: void
     */
    mYPos = yPos;
}

int GameObject::GetWidth() {
    /*!
     * Returns the width of the game object
     *
     * Arguments: None
     * Returns: int, the width of the game object
     */
    return mWidth;
}

int GameObject::GetHeight() {
    /*!
     * Returns the height of the game object
     *
     * Arguments: None
     * Returns: int, the height of the game object
     */
    return mHeight;
}

int GameObject::GetFrame() {
    /*!
     * Returns the frame of the game object
     *
     * Arguments: None
     * Returns: int, the frame of the game object
     */
    return mFrame;
}

void GameObject::SetFrame(int frame) {
    /*!
     * Sets the frame of the game object
     *
     * Arguments: int, the frame of the game object
     * Returns: void
     */
    mFrame = frame;
}

std::string GameObject::GetSequence() {
    /*!
     * Returns the frame sequence of the game object
     *
     * Arguments: None
     * Returns: int, the current frame sequence name of the game object
     */
    return mSequence;
}

void GameObject::SetSequence(std::string sequence) {
    /*!
     * Sets the frame sequence of the game object
     *
     * Arguments: std::string, the current frame sequence name of the game object
     * Returns: void
     */
    mSequence = sequence;
}

int GameObject::GetSpeed() {
    /*!
     * Returns the unique speed of the game object
     *
     * Arguments: None
     * Returns: int, the unique speed of the game object
     */
    return mSpeed;
}

void GameObject::SetSpeed(int speed) {
    /*!
     * Sets the unique speed of the game object
     *
     * Arguments: int, the unique speed of the game object
     * Returns: void
     */
    mSpeed = speed;
}

bool GameObject::GetIsDeleted() {
    /*!
     * Returns the deletion status of the game object
     *
     * Arguments: None
     * Returns: bool, the deletion status of the game object
     */
    return mIsDeleted;
}

void GameObject::SetIsDeleted(bool isDeleted) {
    /*!
     * Sets the deletion status of the game object
     *
     * Arguments: bool, the deletion status of the game object
     * Returns: void
     */
    mIsDeleted = isDeleted;
}

ObjectType GameObject::GetObjectType() {
    /*!
     * Returns the object type of the game object
     *
     * Arguments: None
     * Returns: ObjectType, the object type of the game object
     */
    return mObjectType;
}
void GameObject::SetObjectType(ObjectType objectType) {
    /*!
     * Sets the object type of the game object
     *
     * Arguments: ObjecType, the object type of the game object
     * Returns: void
     */
    mObjectType = objectType;
}

void GameObject::AddComponent(Component* component) {
    /*!
     * Adds a component to the game object
     *
     * Arguments: Component*, a game object component to add to mComponents
     * Returns: void
     */
    mComponents.push_back(component);
}

std::vector<SDL_Event> GameObject::GetEvents() {
    /*!
     * Returns a vector of current SDL_Events to process on the game object
     *
     * Arguments: None
     * Returns: std::vector<SDL_Event>, vector of SDL_Events to process
     */
    return mEvents;
}

std::string GameObject::GetTag() {
    /*!
     * Returns a String tag that denotes the create function of the game object
     *
     * Arguments: None
     * Returns: String, the create function name
     */
    return mTag;
}