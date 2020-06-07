#ifndef HG_MOBS_H
#define HG_MOBS_H

#include "polygons.h"
#include "game_positions.h"
#include "game_textures.h"

class Mob {
    public:
        Mob();
        ~Mob();
        Mob(const Mob& source) = delete;
        Mob& operator=(const Mob& source) = delete;

        void move(void);
        void setPosition(LevelPosition pos);
        void setLTexture(LTexture* texture);
        void render(CameraRelativePosition position);
        LevelPosition m_position;
        int getWidth() const;
        int getHeight() const;
        void setSprite(int row, int col);
        BoundingBox getBoundingBox() const;
    private:
        PhysicsPosition m_world_position;
        SDL_Rect m_clip;
        LTexture* m_ltexture;
        int m_width;
        int m_height;
};

class PolyMob {
    public:
        PolyMob() = delete;
        PolyMob(int count);
        ~PolyMob();
        PolyMob(const PolyMob& source) = delete;
        PolyMob& operator=(const PolyMob& source) = delete;

    private:
        Polygon m_model;
        Polygon m_transformed;
        SDL_Point* m_points;
};

#endif /* HG_MOBS_H */
