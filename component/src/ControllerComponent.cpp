#include "ControllerComponent.hpp"


ControllerComponent::ControllerComponent(){
}

ControllerComponent::~ControllerComponent(){
}

void ControllerComponent::Update(GameObject* g) {
    int i = 0;
    int j = 0
    SDL_Event event;
    SDL_StartTextInput();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a) {
          i -= 1;
        }
        else if (event.key.keysym.sym == SDLK_d) {
          i += 1;
        }
        else if (event.key.keysym.sym == SDLK_w) {
          j -= 1;
        }
        else if (event.key.keysym.sym == SDLK_s) {
          j += 1;
        }
      }
      else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_a) {
          i += 1;
        }
        else if (event.key.keysym.sym == SDLK_d) {
          i -= 1;
        }
        else if (event.key.keysym.sym == SDLK_w) {
          j += 1;
        }
        else if (event.key.keysym.sym == SDLK_s) {
          j -= 1;
        }
      }
    }
    if(i != 0) {
      g->send(111, i);
    }
    if(j != 0) {
      g->send(112, i);
    }
}
