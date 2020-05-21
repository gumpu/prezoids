#ifndef HG_GAME_POSITIONS_H
#define HG_GAME_POSITIONS_H


/* =========================================================================== */
/* A position in the world, used for physics */
class PhysicsPosition {
    public:
        PhysicsPosition();
        float x;
        float y;
};


/* A position relative to the level */
class LevelPosition {
    public:
        LevelPosition();
        int x;
        int y;
};


/* A position in relative to the camera's field of vision */
class CameraRelativePosition {
    public:
        int x;
        int y;
};

class BoundingBox {
    public:
        int x;
        int y;
        int w;
        int h;
};


#endif /* HG_GAME_POSITIONS_H */
