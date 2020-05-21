#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "game_textures.h"
#include "camera.h"
#include "start_screen_state.h"

StartScreenState::StartScreenState()
    : m_background(NULL), m_text_texture(), m_frame(0)
{
    m_frame = 1;
    m_background = loadTexture("Images/start_screen_background.png");
}

StartScreenState::~StartScreenState()
{
   if (m_background != NULL) {
        SDL_DestroyTexture(m_background);
   }
}

void StartScreenState::render(Camera& camera)
{
    LevelPosition p1;
    p1.x = 20;
    p1.y = 20;
    SDL_Color text_color = {0, 0, 0, 255};
    camera.center(p1, SCREEN_WIDTH, SCREEN_HEIGHT);
    camera.render(m_background);
    sprintf(m_buffer, "Frame: %08X", m_frame);
    m_text_texture.loadFromText(m_buffer, text_color);
    m_text_texture.render(40, 40);
    // m_text_texture.render( ( SCREEN_WIDTH - m_text_texture.getWidth() ) / 2, ( SCREEN_HEIGHT - m_text_texture.getHeight() ) / 2 );
    m_frame++;
}



/* ------------------------ end of file -------------------------------*/
