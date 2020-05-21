#ifndef HG_TILES_H
#define HG_TILES_H

class Tile {
    public:
        static const int s_width{ 32 };
        static const int s_height{ 32 };
        Tile();
        ~Tile();
        Tile(const Tile& source);
        Tile& operator=(const Tile& source);
        void setPosition(int x, int y);
        LevelPosition m_position;
        SDL_Rect m_clip;
};
/* --------------------------------------------------------------------*/

class TileMap {
    public:
        TileMap();
        ~TileMap();
        TileMap(const TileMap& source);
        TileMap& operator=(const TileMap& source);
        void render(Camera& camera);
        void setupLevel(void);
        int getTileIndex(int column, int row);
    private:
        LTexture m_tile_atlas;
        Tile* m_tiles;
        int m_number_of_rows;
        int m_number_of_columns;
};
#endif /* HG_TILES_H */
