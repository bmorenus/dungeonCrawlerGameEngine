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
TileMap::TileMap(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* ren) {
    if (nullptr == ren) {
        SDL_Log("No valid renderer found");
    }

    mRows = rows;
    mCols = cols;
    mTileWidth = _TileWidth;
    mTileHeight = _TileHeight;
    mMapX = _mapX;
    mMapY = _mapY;
    // Load the TileMap Image
    // This is the image that will get
    // sliced into smaller subsections of individual tiles.
    mTileSpriteSheet = SDL_LoadBMP(tileSheetFileName.c_str());

    if (nullptr == mTileSpriteSheet) {
        SDL_Log("Failed to allocate surface");
    } else {
        mTexture = SDL_CreateTextureFromSurface(ren, mTileSpriteSheet);
    }

    // Setup the TileMap array
    // This sets each tile to '0'
    mTiles = new int[mMapX * mMapY];
    for (int i = 0; i < mMapX * mMapY; i++) {
        mTiles[i] = -1;  // Default value is no tile.
    }
}

TileMap::~TileMap() {
    SDL_DestroyTexture(mTexture);
    delete[] mTiles;
}

// Helper function to gegenerate a simlpe map
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

// Sets a tile a certain type
void TileMap::SetTile(int x, int y, int type) {
    mTiles[y * mMapX + x] = type;
}

// Returns what the tile is at a specific position.
int TileMap::GetTileType(int x, int y) {
    return mTiles[y * mMapX + x];
}

// render TileMap
void TileMap::Render(SDL_Renderer* renderer) {
    if (nullptr == renderer) {
        SDL_Log("No valid renderer found");
    }

    SDL_Rect Src, Dest;
    for (int y = 0; y < mMapY; y++) {
        for (int x = 0; x < mMapX; x++) {
            int currentTile = GetTileType(x, y);
            if (currentTile > -1) {
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % mCols) * mTileWidth;
                Src.y = (currentTile / mRows) * mTileHeight;
                Src.w = mTileWidth;
                Src.h = mTileHeight;
                // Render our Tile at this location
                Dest.x = x * mTileWidth;
                Dest.y = y * mTileHeight;
                Dest.w = mTileWidth;
                Dest.h = mTileHeight;
                SDL_RenderCopy(renderer, mTexture, &Src, &Dest);
            }
        }
    }
}
