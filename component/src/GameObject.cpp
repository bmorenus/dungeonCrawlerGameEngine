#include "GameObject.hpp"
#include <typeinfo>
#include <iostream>
#include "Component.hpp"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

void GameObject::Update(){
  for (int i = 0; i < list_components.size(); i++)
  {
    if (list_components[i] != NULL)
    {
      list_components[i]->Update(this);
    }
  }

}


void GameObject::Render(SDL_Renderer* ren){
  for (int i = 0; i < list_components.size(); i++)
  {
    if (list_components[i] != NULL)
    {
      list_components[i]->Render(ren);
    }
  }
}

void GameObject::AddComponent(Component* c){
    list_components.push_back(c);
}

void GameObject::send(int message1, int message2) {
  for (int i = 0; i < list_components.size(); i++)
  {
    if (list_components[i] != NULL)
    {
      list_components[i]->receive(message1, message2);
    }
  }
}
