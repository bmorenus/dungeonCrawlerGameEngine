#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <string>

#include "Component.hpp"
#include "TinyMath.hpp"

class GameObject;

class TileMapComponent : public Component {
   public:
    /**
     * Constructor
     */
    TileMapComponent(SDL_Texture* texture, int tileWidth, int tileHeight, int cols, int rows);
    /**
     * Constructor
     */
    ~TileMapComponent();
    /**
     * Update the tile position and frame
     */
    void Update(GameObject& gameObject, int frame) override;
    /**
     * Render the tile map
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    SDL_Texture* mTexture = nullptr;
    int mTileWidth = -1;
    int mTileHeight = -1;
    int mCols = -1;
    int mRows = -1;
};

#endif
