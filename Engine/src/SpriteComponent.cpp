#include "SpriteComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

SpriteComponent::SpriteComponent(SDL_Texture* texture) {
    mTexture = texture;
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(mTexture);
}

void SpriteComponent::Update(GameObject& gameObject) {
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    SDL_Rect src, dest;

    std::string sequenceName = gameObject.GetSequence();
    std::unordered_map<std::string, std::vector<Frame*>>::iterator it;

    it = mFrameSequenceMap.find(sequenceName);
    std::vector<Frame*> frameSequence = it->second;

    int frameIndex = gameObject.GetFrame();
    if (frameIndex >= frameSequence.size()) {
        frameIndex = 0;
    }
    Frame* frame = frameSequence[frameIndex];
    gameObject.SetFrame(frameIndex + 1);

    int xPos = gameObject.GetX();
    int yPos = gameObject.GetY();

    src.x = frame->x;
    src.y = frame->y;
    src.w = frame->w;
    src.h = frame->h;

    SDL_RendererFlip flip;
    if (!frame->reverse) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }

    dest.x = xPos - (gameObject.GetWidth() / 2);
    dest.y = yPos - (gameObject.GetWidth() / 2);
    dest.w = gameObject.GetWidth();
    dest.h = gameObject.GetHeight();

    SDL_RenderCopyEx(renderer,
                     mTexture,
                     &src,
                     &dest,
                     0,
                     NULL,
                     flip);
    // SDL_RenderCopy(renderer, mTexture, &src, &dest);
}

void SpriteComponent::AddFrameSequence(std::string name,
                                       std::vector<Frame*> frameSequence) {
    mFrameSequenceMap.insert({name, frameSequence});
}
