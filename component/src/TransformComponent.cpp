#include "TransformComponent.hpp"

TransformComponent::TransformComponent(Vec2D s, Vec2D p){
  position_next = p;
  velocity = s;
}

TransformComponent::~TransformComponent(){
}

void TransformComponent::receive(int message1, int message2){
  if (message1 == 123) {
    position_next.x = position.x + velocity.x * message2 * dt;
    position_next.y = position.y + velocity.y * message2 * dt;

  } else if(message1 == 124) {
    dt = message2;
  }
}

void TransformComponent::Update(GameObject* g) {
  if (position.x != position_next.x || position.y != position_next.y) {
    position = position_next;
    g->send(125, position.x);
    g->send(126, position.y);
  }
}
