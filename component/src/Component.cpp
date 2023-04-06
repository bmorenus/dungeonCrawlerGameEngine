#include "Component.hpp"
Component::Component(){
}

Component::~Component(){
}

void Component::Update(GameObject* g){
  //std::cout << "wrong update" << "\n";
}

void Component::Render(SDL_Renderer* ren){
  //std::cout << "wrong Render" << "\n";
}

void Component::receive(int message1, int message2){
  //std::cout << "wrong receive" << "\n";
}
