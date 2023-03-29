#include "SpriteComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

SpriteComponent::SpriteComponent(SDL_Texture* texture) {
    mTexture = texture;
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void SpriteComponent::SetPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

int SpriteComponent::GetX() {
    return mPosition.x;
}

void SpriteComponent::Update(GameObject& gameObject, int frame) {
    // The part of the image that we want to render
    mCurrentFrame = frame;
    if (mCurrentFrame > 6) {
        mCurrentFrame = 0;
    }

    // The frame of the sprite sheet to be rendered.
    mSrc.x = mCurrentFrame * 75;
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    // Where the rectangle will be rendered at.
    mDest.x = gameObject.GetX();
    mDest.y = 200;
    mDest.w = 128;
    mDest.h = 128;
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_RenderCopy(renderer, mTexture, &mSrc, &mDest);
    SDL_SetRenderTarget(renderer, texture);
}
