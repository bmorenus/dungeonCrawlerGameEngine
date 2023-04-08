#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"


class TransformComponent : public Component{
    public:
        TransformComponent(Vec2D s, Vec2D p);
        ~TransformComponent();
        void Update(GameObject* g);
        void receive(int message1, int message2);
    private:
        Vec2D velocity;
        Vec2D position;
        Vec2D position_next;
        int dt;


};


#endif
