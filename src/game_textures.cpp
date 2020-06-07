#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "globals.h"
#include "game_textures.h"

LTexture::LTexture()
    : m_texture(NULL), m_width(0), m_height(0)
{
}

LTexture::~LTexture()
{
    if (m_texture == NULL) {
        SDL_DestroyTexture(m_texture);
    }
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect render_quad = {x, y, m_width, m_height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(g_renderer, m_texture, clip, &render_quad);
}

bool LTexture::loadFromText(const char* text, SDL_Color color)
{
    bool result = false;

    release();
    SDL_Surface* text_surface = TTF_RenderText_Solid(g_font, text, color);
    if (text_surface != NULL) {
        m_texture = SDL_CreateTextureFromSurface(g_renderer, text_surface);
        if (m_texture == NULL ) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            //Get image dimensions
            m_width = text_surface->w;
            m_height = text_surface->h;
            result = true;
        }
        SDL_FreeSurface(text_surface);
    }

    return result;
}

bool LTexture::loadFromFile(const char* path)
{
    bool result = false;
    SDL_Texture* texture;

    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Failed to load %s\n", path);
    } else {
        texture = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);
        if (texture == NULL) {
            printf("Unable to create texture from %s\n", path);
        } else {
            m_texture = texture;
            m_width = loaded_surface->w;
            m_height = loaded_surface->h;
            result = true;
        }
        SDL_FreeSurface(loaded_surface);
    }

    return result;
}

void LTexture::release()
{
    if (m_texture != NULL) {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}
/* ======================================================================= */

SDL_Texture* loadTexture(const char* path)
{
    SDL_Texture* result = NULL;

    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Failed to load %s\n", path);
    } else {
        result = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);
        if (result == NULL) {
            printf("Unable to create texture from %s\n", path);
        }
        SDL_FreeSurface(loaded_surface);
    }
    return result;
}

/* ------------------------ end of file -------------------------------*/
