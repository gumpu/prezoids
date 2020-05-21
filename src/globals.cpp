#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "globals.h"

/* --------------------------------------------------------------------*/
// Global variables
//
// The window we'll be rendering to
SDL_Window* g_window = NULL;
// Window Renderer
SDL_Renderer* g_renderer = NULL;
// Game controller
SDL_Joystick* g_game_controller = NULL;
// Game font
TTF_Font* g_font = NULL;
/* ------------------------ end of file -------------------------------*/
