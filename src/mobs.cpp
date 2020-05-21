#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_textures.h"
#include "game_positions.h"
#include "mobs.h"

Mob::Mob()
    : m_position(), m_world_position(), m_clip(), m_ltexture(NULL), m_width(0), m_height(0)
{
    m_world_position.x = LEVEL_WIDTH*((rand() & 0xFF)/255.0F);
    m_world_position.y = LEVEL_HEIGHT*((rand() & 0xFF)/255.0F);
    m_clip.w = 32;
    m_clip.h = 32;
    // Randomly select one of the four sprites
    int n = rand()&0x1;
    m_clip.x = 32*n;
    n = rand()&0x1;
    m_clip.y = 32*n;
}

Mob::~Mob()
{
    m_ltexture = NULL;
}

BoundingBox Mob::getBoundingBox(void)
{
    BoundingBox bb;
    bb.w = m_width;
    bb.h = m_height;
    bb.x = m_position.x - bb.w/2;
    bb.y = m_position.y - bb.h/2;
    return bb;
}

int Mob::getWidth(void)
{
    return m_width;
}

int Mob::getHeight(void)
{
    return m_height;
}

void Mob::render(CameraRelativePosition position)
{
    m_ltexture->render(position.x, position.y, &m_clip);
}

void Mob::move(void)
{
    float dx = 5*((rand() & 0xFF)/255.0F - 0.5F);
    float dy = 5*((rand() & 0xFF)/255.0F - 0.5F);
    m_world_position.x += dx;
    m_world_position.y += dy;
    if (m_world_position.x < 0.0F) {
        m_world_position.x = 0.0F;
    } else if (m_world_position.x > LEVEL_WIDTH) {
        m_world_position.x = (float)(LEVEL_WIDTH);
    }
    if (m_world_position.y < 0.0F) {
        m_world_position.y = 0.0F;
    } else if (m_world_position.y > LEVEL_HEIGHT) {
        m_world_position.y = (float)(LEVEL_HEIGHT);
    }
    m_position.x = (int)m_world_position.x;
    m_position.y = (int)m_world_position.y;
}

void Mob::setLTexture(LTexture* texture)
{
    m_ltexture = texture;
}

void Mob::setPosition(LevelPosition pos)
{
    m_position = pos;
}

void Mob::setSprite(int row, int col)
{
    m_clip.x = 32*col;
    m_clip.y = 32*row;
}

/* ------------------------ end of file -------------------------------*/
