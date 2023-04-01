#include "TileMapComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

TileMapComponent::TileMapComponent(SDL_Texture* texture, int tileWidth, int tileHeight, int cols, int rows) {
    mTexture = texture;
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    mCols = cols;
    mRows = rows;
}

TileMapComponent::~TileMapComponent() {
    SDL_DestroyTexture(mTexture);
}

void TileMapComponent::Update(GameObject& gameObject, int frame) {
}

void TileMapComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    SDL_Rect src, dest;

    int frame = gameObject.GetFrame();
    int xPos = gameObject.GetX();
    int yPos = gameObject.GetY();

    src.x = (frame % mCols) * mTileWidth;
    src.y = (frame / mRows) * mTileHeight;
    src.w = mTileWidth;
    src.h = mTileHeight;

    dest.x = xPos * mTileWidth;
    dest.y = yPos * mTileHeight;
    dest.w = mTileWidth;
    dest.h = mTileHeight;

    SDL_RenderCopy(renderer, mTexture, &src, &dest);
}
