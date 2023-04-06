#include "TileMapComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

TileMapComponent::TileMapComponent(SDL_Texture* texture, TileMap* tileMap) {
    mTexture = texture;
    mTileMap = tileMap;
}

TileMapComponent::~TileMapComponent() {
    SDL_DestroyTexture(mTexture);
}

void TileMapComponent::Update(GameObject& gameObject) {
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

    dest.x = gameObject.GetX() - (gameObject.GetWidth() / 2);
    dest.y = gameObject.GetY() - (gameObject.GetHeight() / 2);
    dest.w = gameObject.GetWidth();
    dest.h = gameObject.GetHeight();

    SDL_RenderCopy(renderer, mTexture, &src, &dest);
}
