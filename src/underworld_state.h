#ifndef HG_UNDERWORLD_STATE_H
#define HG_UNDERWORLD_STATE_H

class UnderWorldState {
    public:
        UnderWorldState();
        ~UnderWorldState();
        UnderWorldState(const UnderWorldState& source);
        UnderWorldState& operator=(const UnderWorldState& source);

        int getWidth(void);
        int getHeight(void);
        void render(Camera& camera);
        void movePlayer(int delta_x, int delta_y);

        void setupTestLevel(void);
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
