#ifndef HG_MOBS_H
#define HG_MOBS_H

class Mob {
    public:
        Mob();
        ~Mob();
        Mob(const Mob& source);
        Mob& operator=(const Mob& source);

        void move(void);
        void setPosition(LevelPosition pos);
        void setLTexture(LTexture* texture);
        void render(CameraRelativePosition position);
        LevelPosition m_position;
        int getWidth(void);
        int getHeight(void);
        void setSprite(int row, int col);
        BoundingBox getBoundingBox(void);
    private:
        PhysicsPosition m_world_position;
        SDL_Rect m_clip;
        LTexture* m_ltexture;
        int m_width;
        int m_height;
};


#endif /* HG_MOBS_H */
