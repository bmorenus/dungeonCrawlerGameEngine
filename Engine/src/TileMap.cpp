#include "TileMap.hpp"

#include <iomanip>
#include <iostream>

// Creates a new tile map.
// rows and cols are how many different tiles there are in the sprite sheet
//
// _TileWidth and _TileHeight are the size of each individual
// tile in the sprite sheet.
// (Typically this works best if they are square for this implementation.)
//
// _mapX, and _mapY are the size of the tilemap. This is the actual
// number of tiles in the game that the player sees, not how many tiles
// are in the actual sprite sheet file loaded.
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

void TileMap::GenerateSimpleMap() {
    for (int y = 0; y < mMapY; y++) {
        for (int x = 0; x < mMapX; x++) {
            if (y == 0) {
                SetTile(x, y, 12);
            }
            if (y == mMapY - 1) {
                SetTile(x, y, 0);
            }
        }
    }
}

void TileMap::PrintMap() {
    for (int y = 0; y < mMapY; y++) {
        for (int x = 0; x < mMapX; x++) {
            std::cout << std::setw(3) << GetTileType(x, y);
        }
        std::cout << "\n";
    }
}

void TileMap::SetTile(int x, int y, int type) {
    mTiles[y * mMapX + x] = type;
}

int TileMap::GetTileType(int x, int y) {
    return mTiles[y * mMapX + x];
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

int TileMap::GetTileCols() {
    return mMapX;
}

int TileMap::GetTileRows() {
    return mMapY;
}
