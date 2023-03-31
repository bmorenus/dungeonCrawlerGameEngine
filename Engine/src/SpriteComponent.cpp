#include "SpriteComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

SpriteComponent::SpriteComponent(SDL_Texture* texture) {
    mTexture = texture;
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(mTexture);
}

void SpriteComponent::Update(GameObject& gameObject, int frame) {
    int currentFrame = gameObject.GetFrame();
    if (currentFrame > 6) {
        gameObject.SetFrame(0);
    } else {
        gameObject.SetFrame(currentFrame + 1);
    }
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    SDL_Rect src, dest;

    int currentFrame = gameObject.GetFrame();
    int xPos = gameObject.GetX();
    int yPos = gameObject.GetY();

    src.x = currentFrame * 75;
    src.y = 0;
    src.w = 75;
    src.h = 87;

    dest.x = xPos;
    dest.y = yPos;
    dest.w = 128;
    dest.h = 128;

    SDL_RenderCopy(renderer, mTexture, &src, &dest);
}
