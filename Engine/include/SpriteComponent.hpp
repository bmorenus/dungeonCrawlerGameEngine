#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Component.hpp"

class GameObject;

struct Frame {
    int x, y, w, h;
    bool reverse;

    Frame(int _x = 0, int _y = 0, int _w = 0, int _h = 0, bool _reverse = false) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        reverse = _reverse;
    }
};

class SpriteComponent : public Component {
   public:
    /**
     * Constructor
     */
    SpriteComponent(SDL_Texture* texture);
    /**
     * Destructor
     */
    ~SpriteComponent();

    /**
     * Update the sprites position and frame
     */
    void Update(GameObject& gameObject) override;

    /**
     * Render the sprite
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

    /*!
     * Adds the provided frame sequence to the map of potential animations that the Sprite Component can render
     */
    void AddFrameSequence(std::string sequenceName, std::vector<Frame*> frameSequence);

   private:
    // An SDL Surface contains pixel data to draw an image
    SDL_Texture* mTexture = nullptr;
    std::unordered_map<std::string, std::vector<Frame*>> mFrameSequenceMap;
};

#endif
