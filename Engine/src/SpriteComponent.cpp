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
    int currentFrame = gameObject.GetFrame();
    if (currentFrame > 6) {
        gameObject.SetFrame(0);
    } else {
        gameObject.SetFrame(currentFrame + 1);
    }
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    SDL_Rect src, dest;

    std::cout << "Rendering" << std::endl;
    std::string sequenceName = gameObject.GetSequence();
    std::cout << "SequenceName: " << sequenceName << std::endl;
    std::unordered_map<std::string, std::vector<Frame*>>::iterator it;

    it = mFrameSequenceMap.find(sequenceName);
    std::cout << "null check" << std::endl;
    std::vector<Frame*> frameSequence = it->second;
    std::cout << "null checked" << std::endl;

    for (int i = 0; i < frameSequence.size(); i++) {
        std::cout << "Frame sequence x: " << frameSequence[i]->x << std::endl;
    }

    int frameIndex = gameObject.GetFrame();
    if (frameIndex >= frameSequence.size()) {
        frameIndex = 0;
    }
    std::cout << "Frame index: " << frameIndex << std::endl;
    std::cout << "Frame sequence size: " << frameSequence.size() << std::endl;
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
