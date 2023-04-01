#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.hpp"
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
     * Update the sprites position and frame
     */
    void Update(GameObject& gameObject, int frame) override;
    /**
     * Render the sprite
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    // An SDL Surface contains pixel data to draw an image
    SDL_Texture* mTexture = nullptr;
};

#endif
