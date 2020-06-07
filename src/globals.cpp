#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "globals.h"

/* --------------------------------------------------------------------*/
// Global variables
//
// The window we'll be rendering to
SDL_Window* g_window = nullptr;
// Window Renderer
SDL_Renderer* g_renderer = nullptr;
// Game controller
SDL_Joystick* g_game_controller = nullptr;
// Game font
TTF_Font* g_font = nullptr;
/* ------------------------ end of file -------------------------------*/
