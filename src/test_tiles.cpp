#include <cstdlib>
#include <cstdint>
#include "ut.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "game_textures.h"
#include "camera.h"
#include "tiles.h"

void test_tile_dimensions()
{
    Tile test_tile;

    UAssert(Tile::s_width == 128);
    UAssert(test_tile.m_clip.w == Tile::s_width);
}

void test_tile_map_dimensions()
{
    TileMap test_tilemap;

}

void register_tiles_tests()
{
    URegister(nullptr,  nullptr, TSTFUN(test_tile_dimensions), "Tile dimensions");
    URegister(nullptr,  nullptr, TSTFUN(test_tile_map_dimensions), "Tile map dimensions");
}

/* ------------------------ end of file -------------------------------*/
