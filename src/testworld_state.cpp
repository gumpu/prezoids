#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "globals.h"
#include "camera.h"
#include "testworld_state.h"

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

    for (auto i = 0; i < 100; ++i) {
        pmobs[i] = nullptr;
    }
}

void TestWorldState::setupLevel()
{
    LevelPosition p;
    auto model = Polygon(4);
    model[0].x = 0.0;
    model[0].y = 0.0;
    model[1].x = 0.0;
    model[1].y = 200.0;
    model[2].x = 100.0;
    model[2].y = 200.0;
    model[3].x = 100.0;
    model[3].y = 0.0;

    for (auto i = 0; i < 100; ++i) {
        pmobs[i] = new PolyMob(4);
        pmobs[i]->setModel(model);
        p.x = LEVEL_WIDTH*((rand() & 0xFF)/255.0F);
        p.y = LEVEL_WIDTH*((rand() & 0xFF)/255.0F);
        pmobs[i]->setPosition(p);
        pmobs[i]->setRotation(2*3.141592*((rand() & 0xFF)/255.0F));

    }
}

TestWorldState::~TestWorldState()
{
   if (m_background != nullptr) {
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
    camera.center(m_player_position, getWidth(), getHeight());
//    camera.render(m_background);

    sprintf(m_buffer, "TW: %08X dx %5d dy %5d", m_frame, m_delta_x, m_delta_y);
    m_text_texture.loadFromText(m_buffer, text_color);
    m_text_texture.render(40, 40);

    camera.render(&(m_player));

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    for (auto i = 0; i < 100; ++i) {
        camera.render(pmobs[i]);
    }
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    m_frame++;
    r = r + 0.005;
    if (r > 2.0) {
        r = 0.0;
    }
}

int TestWorldState::getWidth() const
{
    return test_level_width;
}

int TestWorldState::getHeight() const
{
    return test_level_height;
}

/* ------------------------ end of file -------------------------------*/
