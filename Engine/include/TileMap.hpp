#ifndef TILE_H
#define TILE_H

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <string>

/**
 * This is a minimal implementation of a TileMap
 */
class TileMap {
   public:
    /**
     * Constructor for a tilemap
     */
    TileMap(int rows, int cols, int _TileWidth, int _TileHeight, int _mapX,
            int _mapY);
    /**
     * Destructor for a tilemap
     */
    ~TileMap();

    /*!
     * Returns the number of rows of the tile map
     */
    int GetRows();

    /*!
     * Returns the number of columns of the tile map
     */
    int GetCols();

    /*!
     * Returns the width of the tile map
     */
    int GetTileWidth();

    /*!
     * Returns the height of the tile map
     */
    int GetTileHeight();

   private:
    // Dimensions of our TileMap and individual tiles.
    // Used for spiltting up the sprite sheet
    int mRows;
    int mCols;
    // How big each tile is.
    int mTileWidth;
    int mTileHeight;
    // size of our tilemap
    int mMapX;
    int mMapY;
    // Where our TileMap is rendered
    // An SDL Surface contains pixel data to draw our TileMap
    SDL_Surface* mTileSpriteSheet;
    SDL_Texture* mTexture;
    // Stores our tile types
    int* mTiles;
};

#endif
