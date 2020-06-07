#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "overworld_state.h"

OverWorldState::OverWorldState()
    : m_background(), m_player(), m_player_position(),
    m_sprite_sheet(), m_text_texture(), m_frame(0),
    m_delta_x(0), m_delta_y(0)
{
    m_sprite_sheet.loadFromFile("Images/spritesheet1.png");
    m_background = loadTexture("Images/background1.png");
    m_player.setLTexture(&(m_sprite_sheet));
    m_player.setSprite(2, 0);
    m_player_position.x = 400;
    m_player_position.y = 400;
}

OverWorldState::~OverWorldState()
{
   if (m_background != NULL) {
        SDL_DestroyTexture(m_background);
   }
}

void OverWorldState::movePlayer(int delta_x, int delta_y)
{
    int x = m_player_position.x;
    int y = m_player_position.y;
    m_delta_x = delta_x;
    m_delta_y = delta_y;
    x = x + delta_x;
    y = y + delta_y;
    if (x < 100) { x = 100; }
    if (x > 1200) { x = 1200; }
    if (y < 100) { y = 100; }
    if (y > 1200) { y = 1200; }
    m_player_position.x = x;
    m_player_position.y = y;
    m_player.setPosition(m_player_position);
}

void OverWorldState::render(Camera& camera)
{
    SDL_Color text_color = {0, 0, 0, 255};

    camera.center(m_player_position, getWidth(), getHeight());
    camera.render(m_background);

    sprintf(m_buffer, "Frame: %08X  dx %5d dy %5d", m_frame, m_delta_x, m_delta_y);
    m_text_texture.loadFromText(m_buffer, text_color);
    m_text_texture.render(40, 40);

    camera.render(&(m_player));

    m_frame++;
}

int OverWorldState::getWidth() const
{
    return OVER_LEVEL_WIDTH;
}

/* height */
int OverWorldState::getHeight() const
{
    return OVER_LEVEL_WIDTH;
}



/* ------------------------ end of file -------------------------------*/
