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
        LevelPosition getLevelPosition() const;
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

        int len() const { return m_model.len(); };
        int len_sdl() const { return m_model.len()+1; };
        void setModel(Polygon& model);
        SDL_Point* getSDL_Points();
        LevelPosition getLevelPosition() const;
        void transform(CameraRelativePosition pos);
        void render(CameraRelativePosition position);
        int getWidth() const;
        int getHeight() const;
        void setPosition(LevelPosition pos);
        void setRotation(float r);

    private:
        void computeDimensions();

        Polygon m_model;
        Polygon m_transformed;
        SDL_Point* m_points;
        PhysicsPosition m_world_position;
        float m_rotation = 0.0;
        int m_count;
        int m_width = 0;
        int m_height = 0;
};

#endif /* HG_MOBS_H */
