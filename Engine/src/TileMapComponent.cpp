#include "TileMapComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

TileMapComponent::TileMapComponent(SDL_Texture* texture, TileMap* tileMap) {
    /*!
     * Constructor for the TileMapComponent that displays a game tile in
     *   accordance with the specifications / grid of the provided tile map
     *
     * Arguments: SDL_Texture* texture, the texture of the tile map
     *            TileMap* tileMap, object that specifies the grid structure
     *              of the game scene
     */
    mTexture = texture;
    mTileMap = tileMap;
}

TileMapComponent::~TileMapComponent() {
    /*!
     * Destructor for the TileMapComponent
     */
    SDL_DestroyTexture(mTexture);
}

void TileMapComponent::Update(GameObject& gameObject) {
    /*!
     * Updates the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to update
     * Returns: void
     */
}

void TileMapComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    /*!
     * Renders the provided game object
     *
     * Arguments: GameObject& gameObject, the game object to render
     *            SDL_Renderer& renderer, the renderer for the scene manager
     * Returns: void
     */
    SDL_Rect src, dest;

    int width = mTileMap->GetTileWidth();
    int height = mTileMap->GetTileHeight();
    int cols = mTileMap->GetCols();
    int rows = mTileMap->GetRows();

    int frame = gameObject.GetFrame();
    int xPos = gameObject.GetX();
    int yPos = gameObject.GetY();

    src.x = 0;
    src.y = 0;
    src.w = width;
    src.h = height;

    dest.x = gameObject.GetX() - (gameObject.GetWidth() / 2);
    dest.y = gameObject.GetY() - (gameObject.GetHeight() / 2);
    dest.w = gameObject.GetWidth();
    dest.h = gameObject.GetHeight();

    SDL_RenderCopy(renderer, mTexture, &src, &dest);
}
