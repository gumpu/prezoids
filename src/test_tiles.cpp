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

void test_tile_dimensions(void)
{
    Tile test_tile;

    UAssert(Tile::s_width == 128);
    UAssert(test_tile.m_clip.w == Tile::s_width);
}

void test_tile_map_dimensions(void)
{
    TileMap test_tilemap;

}

void register_tiles_tests(void)
{
    URegister(NULL,  NULL, TSTFUN(test_tile_dimensions), "Tile dimensions");
    URegister(NULL,  NULL, TSTFUN(test_tile_map_dimensions), "Tile map dimensions");
}

/* ------------------------ end of file -------------------------------*/
