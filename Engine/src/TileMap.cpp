#include "TileMap.hpp"

#include <iomanip>
#include <iostream>

TileMap::TileMap(int rows, int cols, int _TileWidth, int _TileHeight,
                 int _mapX, int _mapY) {
    /*!
     * Constructor for the TileMap that specifies the dimensions of the tile
     *   grid used by the scene manager to place tiles in the correct area
     *
     * Arguments: int rows, the number of rows in the tile map
     *            int cols, the number of columns in the tile map
     *            int _TileWidth, the width of a single tile in the grid
     *            int _TileHeight, the height of a single tile in the grid
     *            int _mapX, the number of tiles in a row
     *            int _mapY, the height of tiles in a column
     */
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
    /*!
     * Destructor for the TileMap
     */
    SDL_DestroyTexture(mTexture);
    std::cout << "Deleting TileMap" << std::endl;
    delete[] mTiles;
}

int TileMap::GetRows() {
    /*!
     * Returns the number of rows of the tile map
     *
     * Arguments: None
     * Returns: int, the number of rows of the tile map
     */
    return mRows;
}

int TileMap::GetCols() {
    /*!
     * Returns the number of columns of the tile map
     *
     * Arguments: None
     * Returns: int, the number of columns of the tile map
     */
    return mCols;
}

int TileMap::GetTileWidth() {
    /*!
     * Returns the width of the tile map
     *
     * Arguments: None
     * Returns: int, the width of the tile map
     */
    return mTileWidth;
}

int TileMap::GetTileHeight() {
    /*!
     * Returns the height of the tile map
     *
     * Arguments: None
     * Returns: int, the height of the tile map
     */
    return mTileHeight;
}
