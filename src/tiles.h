#ifndef HG_TILES_H
#define HG_TILES_H

class Tile {
    public:
        static const int s_width{ 4*32 };
        static const int s_height{ 4*32 };
        Tile();
        ~Tile();

        Tile(const Tile& source) = delete;
        Tile& operator=(const Tile& source) = delete;

        void setPosition(int x, int y);
        void setTileShape(int c, int r);
        LevelPosition m_position;
        SDL_Rect m_clip;
};

/* --------------------------------------------------------------------*/

class TileMap {
    public:
        TileMap();
        ~TileMap();

        TileMap(const TileMap& source) = delete;
        TileMap& operator=(const TileMap& source) = delete;

        void render(Camera& camera);
        void setupTilePositions(void);
        int getTileIndex(int column, int row);
        void setupTestLevel(void);
    private:
        LTexture m_tile_atlas;
        Tile* m_tiles;
        int m_number_of_rows;
        int m_number_of_columns;
};

#endif /* HG_TILES_H */
