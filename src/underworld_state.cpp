#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "globals.h"
#include "game_textures.h"
#include "camera.h"
#include "mobs.h"
#include "tiles.h"
#include "underworld_state.h"


UnderWorldState::UnderWorldState()
    : m_tile_atlas(), m_tile_map(), m_player(), m_player_position(),
    m_sprite_sheet(), m_text_texture(), m_frame(0),
    m_delta_x(0), m_delta_y(0)
{
    m_sprite_sheet.loadFromFile("Images/spritesheet1.png");
    m_player.setLTexture(&(m_sprite_sheet));
    m_player.setSprite(2, 0);
    m_player_position.x = 400;
    m_player_position.y = 400;
    m_tile_map.setupLevel();
}

UnderWorldState::~UnderWorldState()
{
    // Nothing
}


int UnderWorldState::getWidth(void)
{
    return UNDER_LEVEL_WIDTH;
}

/* height */
int UnderWorldState::getHeight(void)
{
    return UNDER_LEVEL_WIDTH;
}

void UnderWorldState::movePlayer(int delta_x, int delta_y)
{
    int x = m_player_position.x;
    int y = m_player_position.y;
    m_delta_x = delta_x;
    m_delta_y = delta_y;
    x = x + delta_x;
    y = y + delta_y;
    if (x < 100) { x = 100; }
    if (x > (getWidth() - 100)) { x = getWidth() - 100; }
    if (y < 100) { y = 100; }
    if (y > (getHeight() - 100)) { y = getHeight() - 100; }
    m_player_position.x = x;
    m_player_position.y = y;
    m_player.setPosition(m_player_position);
}

void UnderWorldState::render(Camera& camera)
{
    SDL_Color text_color = {0, 0, 0, 255};

    // Center on the player, so that when the player
    // moves we also move the camera
    camera.center(m_player_position, getWidth(), getHeight());

    m_tile_map.render(camera);

    sprintf(m_buffer, "Frame: %08X  dx %5d dy %5d", m_frame, m_delta_x, m_delta_y);
    m_text_texture.loadFromText(m_buffer, text_color);
    m_text_texture.render(40, 40);

    camera.render(&(m_player));

    m_frame++;
}



/* ------------------------ end of file -------------------------------*/
