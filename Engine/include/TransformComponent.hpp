#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"

class GameObject;

class TransformComponent : public Component {
   public:
    /*!
     * Constructor for the TransformComponent that changes the positional state of the game object to which it is attached
     */
    TransformComponent();

    /*!
     * Destructor for the TransformComponent
     */
    ~TransformComponent();

    /*!
     * Updates the provided game object
     */
    void Update(GameObject& gameObject) override;

    /*!
     * Renders the provided game object
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
};

#endif
