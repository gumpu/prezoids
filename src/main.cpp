#include <cassert>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_limits.h"
#include "game_positions.h"
#include "globals.h"
#include "game_textures.h"
#include "camera.h"
#include "mobs.h"
#include "tiles.h"
#include "start_screen_state.h"
#include "overworld_state.h"
#include "underworld_state.h"
#include "utils.h"

/* ======================================================================= */

enum GameState {
    GS_StartScreen, GS_MainMenu, GS_OverWorld, GS_UnderWorld };
enum GameEvent {
    GE_None, GE_ToMain, GE_ToOverWorld, GE_ToUnderWorld, GE_ToExit };

/* ======================================================================= */

bool process_events(int& delta_x, int& delta_y, enum GameEvent& game_event)
{
    SDL_Event e;
    bool keep_going = true;
    game_event = GE_None;
    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            keep_going = false;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_q) {
                keep_going = false;
            } else if (e.key.keysym.sym == SDLK_g) {
                game_event = GE_ToOverWorld;
            } else if (e.key.keysym.sym == SDLK_u) {
                game_event = GE_ToUnderWorld;
            }
        } else if (e.type == SDL_JOYAXISMOTION) {
            if (e.jaxis.which == 0) {
                if (e.jaxis.axis == 0) {
                    int delta = (e.jaxis.value >> 11);
                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                        delta_x = delta;
                    } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                        delta_x = delta;
                    } else {
                        delta_x = 0;
                    }
                } else if (e.jaxis.axis == 1) {
                    int delta = (e.jaxis.value >> 11);
                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                        delta_y = delta;
                    } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                        delta_y = delta;
                    } else {
                        delta_y = 0;
                    }
                }
            }
        }
    }
    return keep_going;
}

/* --------------------------------------------------------------------*/
void main_loop2(void)
{
    enum GameState current_game_state = GS_StartScreen;
    enum GameEvent game_event = GE_None;
    bool keep_going = true;
    int delta_x = 0;
    int delta_y = 0;
    Camera camera;
    StartScreenState start_screen_state;
    OverWorldState over_world_state;
    UnderWorldState under_world_state;

    under_world_state.setupTestLevel();

    while (keep_going) {
        keep_going = process_events(delta_x, delta_y, game_event);

        /* Process game event */
        switch(game_event) {
            case GE_ToOverWorld:
                current_game_state = GS_OverWorld;
                break;
            case GE_ToUnderWorld:
                current_game_state = GS_UnderWorld;
                break;
            case GE_None:
            default:
                break;
        }

        SDL_RenderClear(g_renderer);
        switch (current_game_state) {
            case GS_StartScreen:
                start_screen_state.render(camera);
                break;
            case GS_MainMenu:
                break;
            case GS_OverWorld:
                over_world_state.movePlayer(delta_x, delta_y);
                over_world_state.render(camera);
                break;
            case GS_UnderWorld:
                under_world_state.movePlayer(delta_x, delta_y);
                under_world_state.render(camera);
                break;
            default:
                break;
        }
        SDL_RenderPresent(g_renderer);
    }
}

/* ======================================================================= */


#if 0
void main_loop(void)
{
    bool keep_going = true;
    SDL_Event e;
    SDL_Texture* texture = NULL;
    LTexture test_ltexture;
    Camera camera;

    int x = 450;
    int y = 450;
    texture = loadTexture("Images/background1.png");
    test_ltexture.loadFromFile("Images/spritesheet1.png");

    LevelPosition p1;
    LevelPosition p2;
    Mob mob1;
    p1.x = 300;
    p1.y = 200;
    p2 = p1;
    mob1.setPosition(p1);
    mob1.setLTexture(&test_ltexture);
    mob1.setSprite(2, 0);
    double cpu_usage = 0.0;
    int k = 0;

#define COUNT 10
    Mob* mobs[COUNT];

    for (int i = 0; i < COUNT; i++) {
        mobs[i] = new Mob();
        mobs[i]->setPosition(p2);
        mobs[i]->setLTexture(&test_ltexture);
    }
    camera.center(p1);

    int delta_x = 0;
    int delta_y = 0;

    while (keep_going) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                keep_going = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) {
                    keep_going = false;
                }
            } else if (e.type == SDL_JOYAXISMOTION) {
                if (e.jaxis.which == 0) {
                    if (e.jaxis.axis == 0) {
                        int delta = (e.jaxis.value >> 11);
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                            delta_x = delta;
                        } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            delta_x = delta;
                        } else {
                            delta_x = 0;
                        }
                    } else if (e.jaxis.axis == 1) {
                        int delta = (e.jaxis.value >> 11);
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                            delta_y = delta;
                        } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            delta_y = delta;
                        } else {
                            delta_y = 0;
                        }
                    }
                }
            }
        }

        x = x + delta_x;
        y = y + delta_y;
        if (x < 0) { x = 0; }
        if (x > 1200) { x = 1200; }
        if (y < 0) { y = 0; }
        if (y > 1200) { y = 1200; }

        p1.x = x;
        p1.y = y;
        mob1.setPosition(p1);
        camera.center(p1);

        double t1 = get_hp_time();
        SDL_RenderClear(g_renderer);
        camera.render(texture);
        camera.render(&mob1);

        for (int i = 0; i < COUNT; i++) {
            mobs[i]->move();
            camera.render(mobs[i]);
        }

        double t2 = get_hp_time();
        cpu_usage += (t2 - t1);
        k++;
        if (k > 100) {
            printf("%f\n", cpu_usage);
            k = 0;
            cpu_usage = 0.0;
        }
        SDL_RenderPresent(g_renderer);
    }
}
#endif

/* ======================================================================= */

bool init(void)
{
    bool result = false;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        if (SDL_NumJoysticks() < 1) {
            printf("Warning: No joysticks connected.\n");
        } else {
            g_game_controller = SDL_JoystickOpen(0);
            if (g_game_controller == NULL) {
                printf("Warning: unable to open the game controller.\n");
            }
        }
        //Create window
        g_window = SDL_CreateWindow(
                "Prezoids",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // Create renderer for window
            g_renderer = SDL_CreateRenderer(
                    g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (g_renderer == NULL) {
                printf("Can't create renderer\n");
            } else {
                SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // Intialize image library
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    printf("SDL Image could not be initialized\n");
                    printf("SDL Image error %s\n", IMG_GetError());
                } else {
                    // Intialize the font library so we can have text
                    if (TTF_Init() == -1) {
                        printf("SDL TTF could not be initialized\n");
                        printf("SDL TTF Error %s\n", TTF_GetError());
                    } else {
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}

bool load_resources(void)
{
    bool result = false;
    g_font = TTF_OpenFont("../Images/DejaVuSansMono-Bold.ttf", 28);
    if (g_font == NULL) {
        printf("Can't load font\n");
    } else {
        result = true;
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
    if (g_game_controller != NULL) {
        SDL_JoystickClose(g_game_controller);
        g_game_controller = NULL;
    }
    if (g_font != NULL) {
        TTF_CloseFont(g_font);
        g_font = NULL;
    }
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/* ===================================================================== */

int main(int argc, char** argv)
{
    if (init()) {
        if (load_resources()) {
            main_loop2();
        }
        finish();
    } else {
        // Some libraries could not be initialized
    }
    return EXIT_SUCCESS;
}

/* ------------------------ end of file -------------------------------*/
