#ifndef HG_CAMERA_H
#define HG_CAMERA_H

class Mob;
class LTexture;
class Tile;

class Camera {
    public:
        Camera();
        ~Camera();
        void center(LevelPosition position, int level_width, int level_height);
        void render(SDL_Texture* texture);
        void render(Mob* mob);
        void render(LTexture& tile_atlas, Tile& tile);
    private:
        SDL_Rect m_camera_rect;
};

#endif /* HG_CAMERA_H */
