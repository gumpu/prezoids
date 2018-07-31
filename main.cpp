#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

// The window we'll be rendering to
static SDL_Window* g_window = NULL;
// The surface contained by the window
static SDL_Surface* screenSurface = NULL;
// Window Renderer
static SDL_Renderer* g_renderer = NULL;




SDL_Texture* loadTexture(const char* path)
{
    SDL_Texture* result;

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


bool init(void)
{
    bool result = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        g_window = SDL_CreateWindow(
                "Prezoids",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // Create renderer for window
            g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
            if (g_renderer == NULL) {
                printf("Can't create renderer\n");
            } else {
                SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Get window surface

                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    printf("SDL Image could not be initialized");
                    printf("SDL Image error %s\n", IMG_GetError());
                } else {
                    screenSurface = SDL_GetWindowSurface(g_window);
                    result = true;
                }
            }
        }
    }
    return result;
}


void finish(void)
{
    if (g_renderer != NULL) {
        SDL_DestroyRenderer(g_renderer);
        g_renderer = NULL;
    }
    if (g_window != NULL) {
        //Destroy window
        SDL_DestroyWindow(g_window);
        g_window = NULL;
    }
    //Quit SDL subsystems
    SDL_Quit();
}

void main_loop(void)
{
    bool keep_going = true;
    SDL_Event e;
    SDL_Texture* texture = NULL;

    texture = loadTexture("Images/test1.png");

    while (keep_going) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                keep_going = false;
            } else if (e.type == SDL_KEYDOWN) {
                printf("Down\n");
                if (e.key.keysym.sym == SDLK_q) {
                    keep_going = false;
                }
            }
        }
        SDL_RenderClear(g_renderer);
        SDL_RenderCopy(g_renderer, texture, NULL, NULL);
        SDL_RenderPresent(g_renderer);
    }
}


int main(int argc, char** argv)
{
    if (init()) {
        SDL_Surface* test = NULL;
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        test = SDL_LoadBMP("Images/test1.bmp");
        SDL_BlitSurface(test, NULL, screenSurface, NULL);
        //Update the surface
        SDL_UpdateWindowSurface(g_window);
        main_loop();
        //Wait two seconds
        SDL_Delay(500);
        finish();
    }
    return EXIT_SUCCESS;
}

/* ------------------------ end of file -------------------------------*/
