#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "game_textures.h"
#include "camera.h"
#include "tiles.h"

/* --------------------------------------------------------------------*/

Tile::Tile() : m_position(), m_clip()
{
    m_clip.w = s_width;
    m_clip.h = s_height;
    // Randomly select one of the 16 tile images
    int n = rand()&0x3;
    m_clip.x = s_width*n;
    n = rand()&0x3;
    m_clip.y = s_height*n;

}

Tile::~Tile() { }

void Tile::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;
}

void Tile::setTileShape(int c, int r)
{
    m_clip.x = s_width * c;
    m_clip.y = s_height * r;
}

/* --------------------------------------------------------------------*/
TileMap::TileMap() : m_tile_atlas(), m_tiles(NULL), m_number_of_rows(0), m_number_of_columns(0)
{
    m_number_of_rows = UNDER_LEVEL_HEIGHT/Tile::s_height;
    m_number_of_columns = UNDER_LEVEL_WIDTH/Tile::s_width;
    m_tiles = new Tile [m_number_of_rows * m_number_of_columns];
    m_tile_atlas.loadFromFile("Images/tile_atlas.png");
}

TileMap::~TileMap()
{
    if (m_tiles != NULL) {
        delete[] m_tiles;
    }
}

int TileMap::getTileIndex(int column, int row)
{
    return column + (row * m_number_of_columns);
}


void TileMap::render(Camera& camera)
{
    for (int c = 0; c < m_number_of_columns; c++) {
        for (int r = 0; r < m_number_of_rows; r++) {
            camera.render(m_tile_atlas, m_tiles[getTileIndex(c, r)]);
        }
    }
}

void TileMap::setupTilePositions(void)
{
    for (int c = 0; c < m_number_of_columns; c++) {
        for (int r = 0; r < m_number_of_rows; r++) {
            int x = c * Tile::s_width;
            int y = r * Tile::s_height;
            m_tiles[getTileIndex(c, r)].setPosition(x, y);
        }
    }
}


void TileMap::setupTestLevel(void)
{
    for (int c = 0; c < m_number_of_columns; c++) {
        for (int r = 0; r < m_number_of_rows; r++) {
            if ((r == 0) && (c == 0)) {
                m_tiles[getTileIndex(c, r)].setTileShape(0, 0);
            } else if ((r == 0) && (c == (m_number_of_columns - 1))) {
                m_tiles[getTileIndex(c, r)].setTileShape(2, 0);
            } else if ((r == (m_number_of_rows - 1)) && (c == 0)) {
                m_tiles[getTileIndex(c, r)].setTileShape(0, 2);
            } else if ((r == (m_number_of_rows - 1)) && (c == (m_number_of_columns - 1))) {
                m_tiles[getTileIndex(c, r)].setTileShape(2, 2);
            } else if (r == 0) {
                m_tiles[getTileIndex(c, r)].setTileShape(1, 0);
            } else if (r == (m_number_of_rows -1)) {
                m_tiles[getTileIndex(c, r)].setTileShape(1, 2);
            } else if (c == (m_number_of_columns -1)) {
                m_tiles[getTileIndex(c, r)].setTileShape(2, 1);
            } else if (c == 0) {
                m_tiles[getTileIndex(c, r)].setTileShape(0, 1);
            } else {
                m_tiles[getTileIndex(c, r)].setTileShape(3, 0);
            }
        }
    }

    m_tiles[getTileIndex(3, 1)].setTileShape(0, 2);
}

/* ------------------------ end of file -------------------------------*/
