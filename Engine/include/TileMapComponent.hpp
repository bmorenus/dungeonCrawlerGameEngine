#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <string>

#include "Component.hpp"
#include "TileMap.hpp"

class GameObject;

class TileMapComponent : public Component {
   public:
    /*!
     * Constructor for the TileMapComponent that displays a game tile in accordance with the specifications / grid of the provided tile map
     */
    TileMapComponent(SDL_Texture* texture, TileMap* tileMap);
    /*!
     * Destructor for the TileMapComponent
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
