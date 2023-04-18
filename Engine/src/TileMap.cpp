#include "TileMap.hpp"

#include <iomanip>
#include <iostream>

TileMap::TileMap(int rows, int cols, int _TileWidth, int _TileHeight,
                 int _mapX, int _mapY) {
    mRows = rows;
    mCols = cols;
    mTileWidth = _TileWidth;
    mTileHeight = _TileHeight;
    mMapX = _mapX;
    mMapY = _mapY;

    mTiles = new int[mMapX * mMapY];
    for (int i = 0; i < mMapX * mMapY; i++) {
        mTiles[i] = -1;  // Default value is no tile.
    }
}

TileMap::~TileMap() {
    SDL_DestroyTexture(mTexture);
    std::cout << "Deleting TileMap" << std::endl;
    delete[] mTiles;
}

int TileMap::GetRows() {
    return mRows;
}

int TileMap::GetCols() {
    return mCols;
}

int TileMap::GetTileWidth() {
    return mTileWidth;
}

int TileMap::GetTileHeight() {
    return mTileHeight;
}
