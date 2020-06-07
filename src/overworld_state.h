#ifndef HG_OVERWORLD_STATE_H
#define HG_OVERWORLD_STATE_H

#include "game_textures.h"
#include "game_positions.h"
#include "camera.h"
#include "mobs.h"

class OverWorldState {
    public:
        OverWorldState();
        ~OverWorldState();
        OverWorldState(const OverWorldState& source);
        OverWorldState& operator=(const OverWorldState& source);

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

#endif /* HG_OVERWORLD_STATE_H */
