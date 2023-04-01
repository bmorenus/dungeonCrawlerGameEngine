#ifndef TILE_H
#define TILE_H

#include <string>

#include "IGraphicsEngineRenderer.hpp"

/**
 * This is a minimal implementation of a TileMap
 */
class TileMap {
   public:
    /**
     * Constructor for a tilemap
     */
    TileMap(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* ren);
    /**
     * Destructor for a tilemap
     */
    ~TileMap();
    /**
     * Temporary function for generating a simple
     * map to display some tiles
     */
    void GenerateSimpleMap();
    /**
     * Function for printing text to console
     */
    void PrintMap();
    /**
     * Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);
    /**
     * Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);
    /**
     * Draw all of the tiles in the tilemap
     */
    void Render(SDL_Renderer* ren);

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
