#include "TileMapComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

TileMapComponent::TileMapComponent(SDL_Texture* texture, TileMap* tileMap) {
    mTexture = texture;
    mTileMap = tileMap;
    // mTileWidth = tileWidth;
    // mTileHeight = tileHeight;
    // mCols = cols;
    // mRows = rows;
}

TileMapComponent::~TileMapComponent() {
    SDL_DestroyTexture(mTexture);
}

void TileMapComponent::Update(GameObject& gameObject, int frame) {
}

void TileMapComponent::Render(GameObject& gameObject, SDL_Renderer* renderer) {
    SDL_Rect src, dest;

    int width = mTileMap->GetTileWidth();
    int height = mTileMap->GetTileHeight();
    int cols = mTileMap->GetCols();
    int rows = mTileMap->GetRows();

    int frame = gameObject.GetFrame();
    int xPos = gameObject.GetX();
    int yPos = gameObject.GetY();

    src.x = (frame % cols) * width;
    src.y = (frame / rows) * height;
    src.w = width;
    src.h = height;

    dest.x = (xPos - (xPos % width)) - 9;
    dest.y = (yPos - (yPos % height)) - 14;
    dest.w = width;
    dest.h = height;

    SDL_RenderCopy(renderer, mTexture, &src, &dest);
}
