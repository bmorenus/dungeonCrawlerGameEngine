#include "SpriteComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

SpriteComponent::SpriteComponent(SDL_Texture* texture) {
    /*!
     * Constructor for the SpriteComponent that renders the game object that
     *    calls it with the provided texture in the constructorr
     *
     * Arguments: SDL_Texture* texture, the desired texture to render the
     *   game object with
     */
    mTexture = texture;
}

SpriteComponent::~SpriteComponent() {
    /*!
     * Destructor for the SpriteComponent
     */
    SDL_DestroyTexture(mTexture);
}

void SpriteComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
}

void SpriteComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
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
    dest.y = yPos - (gameObject.GetHeight() / 2);
    dest.w = gameObject.GetWidth();
    dest.h = gameObject.GetHeight();

    SDL_RenderCopyEx(renderer,
                     mTexture,
                     &src,
                     &dest,
                     0,
                     NULL,
                     flip);
}

void SpriteComponent::AddFrameSequence(std::string name,
                                       std::vector<Frame*> frameSequence) {
    /*!
     * Adds the provided frame sequence to the map of potential animations that
     *   the Sprite Component can render
     *
     * Arguments: String name, the name of the frame sequence for easy look-up
     *            std::vector<Frame*> frameSequence, the vector containing the
     *              frames to iterate over to animate
     * Returns: void
     */
    mFrameSequenceMap.insert({name, frameSequence});
}
