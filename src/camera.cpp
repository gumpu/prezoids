#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "globals.h"
#include "game_textures.h"
#include "mobs.h"
#include "camera.h"
#include "tiles.h"

Camera::Camera() : m_camera_rect()
{
    m_camera_rect.x = 0;
    m_camera_rect.y = 0;
    m_camera_rect.w = SCREEN_WIDTH;
    m_camera_rect.h = SCREEN_HEIGHT;
}

Camera::~Camera() { }

void Camera::render(SDL_Texture* texture)
{
    SDL_RenderCopy(g_renderer, texture, &(m_camera_rect), NULL);
}

void Camera::render(Mob* mob)
{
    CameraRelativePosition pos;
    int w = mob->getWidth();
    int h = mob->getHeight();
    pos.x = mob->m_position.x - w/2;
    pos.y = mob->m_position.y - h/2;
    pos.x = pos.x - m_camera_rect.x;

    if (pos.x < (0-w)) {
        /* Don't render */
    } else {
        if (pos.x < m_camera_rect.w) {
            pos.y = pos.y - m_camera_rect.y;
            if (pos.y < (0-h)) {
                /* Don't render */
            } else {
                if (pos.y > m_camera_rect.h) {
                    /* Don't render */
                } else {
                    mob->render(pos);
                }
            }
        } else {
            /* Don't render */
        }
    }
}

void Camera::render(LTexture& tile_atlas, Tile& tile)
{
    CameraRelativePosition p;
    p.x = m_camera_rect.x - tile.m_position.x;
    p.y = m_camera_rect.y - tile.m_position.y;
    if (p.x >= 0) {
        if (p.y >= 0) {
            if (p.x < SCREEN_WIDTH) {
                if (p.y < SCREEN_HEIGHT) {
                    tile_atlas.render(p.x, p.y, &(tile.m_clip));
                }
            }
        }
    }
}

void Camera::center(LevelPosition position)
{
    int w = m_camera_rect.w;
    int h = m_camera_rect.h;
    int x = position.x - w/2;
    int y = position.y - w/2;

    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    if (x > (LEVEL_WIDTH - w)) { x = LEVEL_WIDTH - w; }
    if (y > (LEVEL_HEIGHT - h)) { y = LEVEL_HEIGHT - h; }
    m_camera_rect.x = x;
    m_camera_rect.y = y;
}

