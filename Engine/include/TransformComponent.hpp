#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"

class GameObject;

class TransformComponent : public Component {
   public:
    TransformComponent();
    ~TransformComponent();
    void Update(GameObject& gameObject) override;
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
};

#endif
