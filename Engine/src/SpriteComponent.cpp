#include "SpriteComponent.hpp"
#include "GameObject.hpp"
#include <iostream>

SpriteComponent::SpriteComponent(){
}

SpriteComponent::~SpriteComponent(){
// TODO: Make sure spritesheet and mTexture are destroyed
// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void SpriteComponent::SetPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

int SpriteComponent::GetX() {
    return mPosition.x;
}

void SpriteComponent::Update(GameObject& gameObject, int frame){
    // The part of the image that we want to render
    mCurrentFrame = frame;
    if(mCurrentFrame>6){
        mCurrentFrame=0;
    }

    // The frame of the sprite sheet to be rendered.
    mSrc.x = mCurrentFrame*75;
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    // Where the rectangle will be rendered at.
    mDest.x = gameObject.GetX();
    mDest.y = 200;
    mDest.w = 128;
    mDest.h = 128;
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, mTexture, &mSrc, &mDest);
}

void SpriteComponent::LoadImage(std::string filePath, SDL_Renderer* renderer){
    mSpriteSheet = SDL_LoadBMP(filePath.c_str());
    if(nullptr == mSpriteSheet){
           SDL_Log("Failed to allocate surface");
    }else{
        SDL_Log("Allocated a bunch of memory to create identical game character");
        mTexture = SDL_CreateTextureFromSurface(renderer, mSpriteSheet);
    }
}
