#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.hpp"
#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class GameObject;

class SpriteComponent : public Component {
   public:
    /**
     * Constructor
     */
    SpriteComponent(SDL_Texture* texture);
    /**
     * Constructor
     */
    ~SpriteComponent();
    /**
     * Initialize the sprite
     */
    void SetPosition(int x, int y);
    int GetX();
    /**
     * Update the sprites position and frame
     */
    void Update(GameObject& gameObject, int frame) override;
    /**
     * Render the sprite
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    Vec2D mPosition;
    unsigned int mCurrentFrame{0};
    unsigned int mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
    SDL_Texture* mTexture = nullptr;

    SDL_Rect mSrc;
    SDL_Rect mDest;
};

#endif
