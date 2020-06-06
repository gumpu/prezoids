#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "game_textures.h"
#include "globals.h"
#include "camera.h"
#include "mobs.h"
#include "testworld_state.h"
#include "polygons.h"

TestWorldState::TestWorldState()
    : m_background(), m_player(), m_player_position(),
    m_sprite_sheet(), m_text_texture(), m_frame(0),
    m_delta_x(0), m_delta_y(0)
{
    m_sprite_sheet.loadFromFile("Images/spritesheet1.png");
    m_background = loadTexture("Images/test_background.png");
    m_player.setLTexture(&(m_sprite_sheet));
    m_player.setSprite(2, 0);
    m_player_position.x = 400;
    m_player_position.y = 400;
}

TestWorldState::~TestWorldState()
{
   if (m_background != NULL) {
        SDL_DestroyTexture(m_background);
   }
}

void TestWorldState::movePlayer(int delta_x, int delta_y)
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

void TestWorldState::render(Camera& camera)
{
    static float r = 0.0;

    SDL_Color text_color = {0, 0, 0, 255};
    Polygon test_polygon(4);

    test_polygon[0].x = 10;
    test_polygon[0].y = 10;
    test_polygon[1].x = 10;
    test_polygon[1].y = 100;
    test_polygon[2].x = 100;
    test_polygon[2].y = 100;
    test_polygon[3].x = 10;
    test_polygon[3].y = 10;

    camera.center(m_player_position, getWidth(), getHeight());
//    camera.render(m_background);

    sprintf(m_buffer, "TW Frame: %08X dx %5d dy %5d", m_frame, m_delta_x, m_delta_y);
    m_text_texture.loadFromText(m_buffer, text_color);
    m_text_texture.render(40, 40);

    camera.render(&(m_player));

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < 160; i = i + 20)
    {
        SDL_Point p = test_polygon.center();
        test_polygon.translate(-p.x, -p.y);
        test_polygon.rotate(r*3.141592);
        test_polygon.translate(200 + i, 200 + i/4);
        SDL_RenderDrawLines(g_renderer, test_polygon.points(), test_polygon.len());
    }
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    m_frame++;
    r = r + 0.005;
    if (r > 2.0) {
        r = 0.0;
    }
}

int TestWorldState::getWidth(void)
{
    return OVER_LEVEL_WIDTH;
}

/* height */
int TestWorldState::getHeight(void)
{
    return OVER_LEVEL_WIDTH;
}

/* ------------------------ end of file -------------------------------*/
