#ifndef HG_TESTWORLD_STATE_H
#define HG_TESTWORLD_STATE_H

#include "game_textures.h"
#include "game_positions.h"
#include "mobs.h"

class Camera;

class TestWorldState {
    public:
        TestWorldState();
        ~TestWorldState();

        TestWorldState(const TestWorldState& source) = delete;
        TestWorldState& operator=(const TestWorldState& source) = delete;

        int getWidth() const;
        int getHeight() const;
        void render(Camera& camera);
        void movePlayer(int delta_x, int delta_y);
        void setupLevel();

    private:
        SDL_Texture* m_background;
        Mob m_player;
        LevelPosition m_player_position;
        LTexture m_sprite_sheet;
        LTexture m_text_texture;
        int m_frame;
        int m_delta_x;
        int m_delta_y;
        char m_buffer[160];

        PolyMob* pmobs[100];
};

#endif /* HG_TESTWORLD_STATE_H */
