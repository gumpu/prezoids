#ifndef HG_UNDERWORLD_STATE_H
#define HG_UNDERWORLD_STATE_H

#include "game_textures.h"
#include "game_positions.h"
#include "mobs.h"
#include "camera.h"
#include "tiles.h"

class UnderWorldState {
    public:
        UnderWorldState();
        ~UnderWorldState();
        UnderWorldState(const UnderWorldState& source);
        UnderWorldState& operator=(const UnderWorldState& source);

        int getWidth() const;
        int getHeight() const;
        void render(Camera& camera);
        void movePlayer(int delta_x, int delta_y);

        void setupTestLevel();
    private:
        SDL_Texture* m_tile_atlas;
        TileMap m_tile_map;
        Mob m_player;
        LevelPosition m_player_position;
        LTexture m_sprite_sheet;
        LTexture m_text_texture;
        int m_frame;
        int m_delta_x;
        int m_delta_y;
        char m_buffer[160];
};

#endif /* HG_UNDERWORLD_STATE_H */
