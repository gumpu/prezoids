#ifndef HG_TESTWORLD_STATE_H
#define HG_TESTWORLD_STATE_H

#include "game_textures.h"
#include "game_positions.h"
#include "mobs.h"
#include "camera.h"

class TestWorldState {
    public:
        TestWorldState();
        ~TestWorldState();
        TestWorldState(const TestWorldState& source);
        TestWorldState& operator=(const TestWorldState& source);

        int getWidth() const;
        int getHeight() const;
        void render(Camera& camera);
        void movePlayer(int delta_x, int delta_y);
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
};

#endif /* HG_TESTWORLD_STATE_H */
