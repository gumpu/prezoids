#include <cassert>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int LEVEL_WIDTH  = 1280;
const int LEVEL_HEIGHT = 1280;
//Screen dimension constants
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 640;
const int JOYSTICK_DEAD_ZONE = 100;

// The window we'll be rendering to
static SDL_Window* g_window = NULL;
// The surface contained by the window
static SDL_Surface* screenSurface = NULL;
// Window Renderer
static SDL_Renderer* g_renderer = NULL;
// Game controller
static SDL_Joystick* g_game_controller = NULL;

/* =========================================================================== */
SDL_Texture* loadTexture(const char* path);

/* =========================================================================== */

double get_hp_time( void )
{
    struct timespec tp;
    (void)clock_gettime( CLOCK_REALTIME, &tp );
    return tp.tv_sec + tp.tv_nsec / 1E9;
}

/* =========================================================================== */
/* A position in the world, used for physics */
class FPos {
    public:
        float x;
        float y;
};

/* A position in relative to the level */
class LPos {
    public:
        int x;
        int y;
};

/* A position in relative to the camera's field of vision */
class CPos {
    public:
        int x;
        int y;
};

/* =========================================================================== */

class BoundingBox {
    public:
        int x;
        int y;
        int w;
        int h;
};

/* =========================================================================== */

class LTexture {
    public:
        LTexture();
        ~LTexture();
        LTexture(const LTexture& source);
        LTexture& operator=(const LTexture& source);
        bool loadFromFile(const char* path);
        void render(int x, int y, SDL_Rect* clip = NULL);

    private:
        SDL_Texture* m_texture;
        int m_width;
        int m_height;
};

LTexture::LTexture()
    : m_texture(NULL), m_width(0), m_height(0)
{
}

LTexture::~LTexture()
{
    if (this->m_texture == NULL) {
        SDL_DestroyTexture(this->m_texture);
    }
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect render_quad = {x, y, this->m_width, this->m_height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(g_renderer, this->m_texture, clip, &render_quad);
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
            this->m_texture = texture;
            this->m_width = loaded_surface->w;
            this->m_height = loaded_surface->h;
            result = true;
        }
        SDL_FreeSurface(loaded_surface);
    }

    return result;
}

/* =========================================================================== */
/* =========================================================================== */

class Mob {
    public:
        Mob();
        ~Mob();
        void move(void);
        void setPosition(LPos pos);
        void setLTexture(LTexture* texture);
        void render(CPos position);
        LPos m_position;
        int getWidth(void);
        int getHeight(void);
        void setSprite(int row, int col);
        BoundingBox getBoundingBox(void);
    private:
        SDL_Rect m_clip;
        LTexture* m_ltexture;
        int m_width;
        int m_height;
        FPos m_world_position;
};

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
    return this->m_width;
}

int Mob::getHeight(void)
{
    return this->m_height;
}

void Mob::render(CPos position)
{
    m_ltexture->render(position.x, position.y, &m_clip);
}

void Mob::move(void)
{
    float dx = 5*((rand() & 0xFF)/255.0F - 0.5F);
    float dy = 5*((rand() & 0xFF)/255.0F - 0.5F);
    this->m_world_position.x += dx;
    this->m_world_position.y += dy;
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
    this->m_ltexture = texture;
}

void Mob::setPosition(LPos pos)
{
    this->m_position = pos;
}

void Mob::setSprite(int row, int col)
{
    this->m_clip.x = 32*col;
    this->m_clip.y = 32*row;
}

Mob::Mob()
{
    this->m_position.x = 0;
    this->m_position.y = 0;
    this->m_ltexture = NULL;
    this->m_width = 32;
    this->m_height = 32;
    this->m_world_position.x = LEVEL_WIDTH*((rand() & 0xFF)/255.0F);
    this->m_world_position.y = LEVEL_HEIGHT*((rand() & 0xFF)/255.0F);

    this->m_clip.w = 32;
    this->m_clip.h = 32;
    // Randomly select one of the four sprites
    int n = rand()&0x1;
    this->m_clip.x = 32*n;
    n = rand()&0x1;
    this->m_clip.y = 32*n;
}

Mob::~Mob()
{
    this->m_ltexture = NULL;
}

/* =========================================================================== */

class Camera {
    public:
        Camera();
        ~Camera();
        void center(LPos position);
        void render(SDL_Texture* texture);
        void render(Mob* mob);
    private:
        SDL_Rect m_camera_rect;
};

Camera::Camera()
{
    this->m_camera_rect.x = 0;
    this->m_camera_rect.y = 0;
    this->m_camera_rect.w = SCREEN_WIDTH;
    this->m_camera_rect.h = SCREEN_HEIGHT;
}

Camera::~Camera() { }

void Camera::render(SDL_Texture* texture)
{
    SDL_RenderCopy(g_renderer, texture, &(this->m_camera_rect), NULL);
}

void Camera::render(Mob* mob)
{
    CPos pos;
    int w = mob->getWidth();
    int h = mob->getHeight();
    pos.x = mob->m_position.x - w/2;
    pos.y = mob->m_position.y - h/2;
    bool render_it = false;
    pos.x = pos.x - this->m_camera_rect.x;

    if (pos.x < (0-w)) {
        /* Don't render */
    } else {
        if (pos.x < m_camera_rect.w) {
            pos.y = pos.y - this->m_camera_rect.y;
            if (pos.y < (0-h)) {
                /* Don't render */
            } else {
                if (pos.y > m_camera_rect.h) {
                    /* Don't render */
                } else {
                    render_it = true;
                    mob->render(pos);
                }
            }
        } else {
            /* Don't render */
        }
    }
}

void Camera::center(LPos position)
{
    int w = m_camera_rect.w;
    int h = m_camera_rect.h;
    int x = position.x - w/2;
    int y = position.y - w/2;

    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    if (x > (LEVEL_WIDTH - w)) { x = LEVEL_WIDTH - w; }
    if (y > (LEVEL_HEIGHT - h)) { y = LEVEL_HEIGHT - h; }
    this->m_camera_rect.x = x;
    this->m_camera_rect.y = y;
}

/* ======================================================================= */

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


/* --------------------------------------------------------------------*/

class StartScreenState {
    public:
        StartScreenState();
        ~StartScreenState();
        void render(Camera& camera);
    private:
        SDL_Texture* background;
};

void StartScreenState::render(Camera& camera)
{
    LPos p1;
    p1.x = 20;
    p1.y = 20;
    camera.center(p1);
    camera.render(this->background);
}

StartScreenState::StartScreenState()
{
    this->background = loadTexture("Images/start_screen_background.png");
}

StartScreenState::~StartScreenState()
{
    // TODO
}


/* ======================================================================= */

enum GameState { StartScreen, MainMenu, OverWorld };
enum GameEvent { None, ToMain, ToOverWorld, ToExit };
/* ======================================================================= */

bool process_events(int& delta_x, int& delta_y, enum GameEvent& game_event)
{
    SDL_Event e;
    bool keep_going = true;
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
    return keep_going;
}


void main_loop2(void)
{
    enum GameState current_game_state = StartScreen;
    enum GameEvent game_event = None;
    bool keep_going = true;
    int delta_x = 0;
    int delta_y = 0;
    Camera camera;
    StartScreenState start_screen_state;

    while (keep_going) {
        keep_going = process_events(delta_x, delta_y, game_event);

        /* Process game event */

        SDL_RenderClear(g_renderer);

        switch (current_game_state) {
            case StartScreen:
                start_screen_state.render(camera);
                break;
            case MainMenu:
                break;
            case OverWorld:
                break;
            default:
                break;
        }

        SDL_RenderPresent(g_renderer);

    }
}


/* ======================================================================= */

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

    LPos p1;
    LPos p2;
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
                //Get window surface
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    printf("SDL Image could not be initialized\n");
                    printf("SDL Image error %s\n", IMG_GetError());
                } else {
                    screenSurface = SDL_GetWindowSurface(g_window);

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

/* ====================================================================== */

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
    }
    IMG_Quit();
    //Quit SDL subsystems
    SDL_Quit();
}

/* ===================================================================== */

int main(int argc, char** argv)
{
    if (init()) {
        SDL_Surface* test = NULL;

        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        // test = SDL_LoadBMP("Images/test1.bmp");
        // SDL_BlitSurface(test, NULL, screenSurface, NULL);
        //Update the surface
        SDL_UpdateWindowSurface(g_window);
        // SDL_Delay(2500);

        main_loop2();

        finish();
    }
    return EXIT_SUCCESS;
}

/* ------------------------ end of file -------------------------------*/
