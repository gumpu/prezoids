#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_textures.h"
#include "game_positions.h"
#include "polygons.h"
#include "mobs.h"

/* --------------------------------------------------------------------*/

Mob::Mob()
    : m_world_position(), m_clip(), m_ltexture(nullptr), m_width(0), m_height(0)
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
    m_width = 32;
    m_height = 32;
}

Mob::~Mob()
{
    m_ltexture = nullptr;
}

BoundingBox Mob::getBoundingBox() const
{
    BoundingBox bb;
    bb.w = m_width;
    bb.h = m_height;
    bb.x = (int)(m_world_position.x) - bb.w/2;
    bb.y = (int)(m_world_position.y) - bb.h/2;
    return bb;
}

int Mob::getWidth() const
{
    return m_width;
}

int Mob::getHeight() const
{
    return m_height;
}

void Mob::render(CameraRelativePosition position)
{
    m_ltexture->render(position.x, position.y, &m_clip);
}

void Mob::move()
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
}

LevelPosition Mob::getLevelPosition() const
{
    LevelPosition p;
    p.x = (int)m_world_position.x;
    p.y = (int)m_world_position.y;
    return p;
}

void Mob::setLTexture(LTexture* texture)
{
    m_ltexture = texture;
}

void Mob::setPosition(LevelPosition pos)
{
    m_world_position.x = (float)pos.x;
    m_world_position.y = (float)pos.y;
}

void Mob::setSprite(int row, int col)
{
    m_clip.x = 32*col;
    m_clip.y = 32*row;
}

/* --------------------------------------------------------------------*/

PolyMob::PolyMob(int count)
    : m_model(count), m_transformed(count), m_points(nullptr),
    m_world_position(), m_rotation(0.0), m_count(count)
{
    m_points = new SDL_Point[count + 1];
}

PolyMob::~PolyMob()
{
    if (m_points != nullptr) {
        delete[] m_points;
    }
}

void PolyMob::computeDimensions()
{
    auto x_min = m_model[0].x;
    auto y_min = m_model[0].y;
    auto x_max = m_model[0].x;
    auto y_max = m_model[0].y;
    for (auto i = 1; i < m_model.len(); ++i) {
        if (m_model[i].x < x_min) {
            x_min = m_model[i].x;
        }
        if (m_model[i].y < y_min) {
            y_min = m_model[i].y;
        }
        if (m_model[i].x > x_max) {
            x_max = m_model[i].x;
        }
        if (m_model[i].y > y_max) {
            y_max = m_model[i].y;
        }
    }
    m_width = (x_max - x_min);
    m_height = (y_max - y_min);
}

int PolyMob::getWidth() const
{
    return m_width;
}

int PolyMob::getHeight() const
{
    return m_height;
}

void PolyMob::setModel(Polygon& model)
{
    for (auto i = 0; i < model.len(); ++i) {
        m_model[i] = model[i];
    }
    computeDimensions();
}

SDL_Point* PolyMob::getSDL_Points()
{
    return nullptr;
}

/* ------------------------ end of file -------------------------------*/
