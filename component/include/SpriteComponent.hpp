#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"
#include "Component.hpp"


/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component {
public:

    /**
     * Constructor
     */
    SpriteComponent(std::string filePath, SDL_Renderer* ren);
    /**
     * Constructor
     */
    ~SpriteComponent();
    /**
     * Initialize the sprite
     */
    void receive(int message1, int message2);
    /**
     * Update the sprites position and frame
     */
    void Update(GameObject* g);

    void Render(SDL_Renderer* ren);
    /**
     * Load a sprite
     */

private:
	unsigned int    mCurrentFrame{0};
	unsigned int    mLastFrame{7};
	SDL_Rect        mSrc;
	SDL_Rect        mDest;
  SDL_Surface * m_surfance;
  SDL_Texture * m_texture;
};

#endif
