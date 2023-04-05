#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <string>

#include "Component.hpp"
#include "TileMap.hpp"

class GameObject;

class TileMapComponent : public Component {
   public:
    /**
     * Constructor
     */
    TileMapComponent(SDL_Texture* texture, TileMap* tileMap);
    /**
     * Constructor
     */
    ~TileMapComponent();
    /**
     * Update the tile position and frame
     */
    void Update(GameObject& gameObject) override;
    /**
     * Render the tile map
     */
    void Render(GameObject& gameObject, SDL_Renderer* renderer) override;

   private:
    SDL_Texture* mTexture = nullptr;
    TileMap* mTileMap = nullptr;
    int mTileWidth = -1;
    int mTileHeight = -1;
    int mCols = -1;
    int mRows = -1;
};

#endif
