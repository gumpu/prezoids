#ifndef HG_CAMERA_H
#define HG_CAMERA_H

#include "game_positions.h"
class Mob;
class PolyMob;
class LTexture;
class Tile;

class Camera {
    public:
        Camera();
        ~Camera();
        void center(LevelPosition position, int level_width, int level_height);
        void render(SDL_Texture* texture) const;
        void render(Mob* mob) const;
        void render(PolyMob* mob) const;
        void render(LTexture& tile_atlas, Tile& tile) const;
    private:
        SDL_Rect m_camera_rect;
};

#endif /* HG_CAMERA_H */
