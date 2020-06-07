#include "ut.h"
#include <SDL.h>
#include "mobs.h"

static void test_mob_creation()
{
    BoundingBox b;
    auto m = Mob();

    b = m.getBoundingBox();

    UAssert(b.w == 32);
    UAssert(b.h == 32);
}

static void test_polymob_creation()
{
    auto model = Polygon(4);
    auto pm = PolyMob(4);

    model[0].x = 0.0;
    model[0].y = 0.0;

    model[1].x = 0.0;
    model[1].y = 200.0;

    model[2].x = 100.0;
    model[2].y = 200.0;

    model[3].x = 100.0;
    model[3].y = 0.0;

    UAssert(pm.len() == 0);
    pm.setModel(model);
    UAssert(pm.len() == 4);

    UAssert(pm.getWidth() == 100);
    UAssert(pm.getHeight() == 200);

    {
        PolyMob* pm2 = new PolyMob(4);
        pm2->setModel(model);
        UAssert(pm2->len() == 4);
        delete pm2;
    }
}

static void test_polymob_transform()
{
    auto model = Polygon(4);
    auto pm = PolyMob(4);
    CameraRelativePosition pos;
    SDL_Point* points = nullptr;

    model[0].x = 0.0;
    model[0].y = 0.0;

    model[1].x = 0.0;
    model[1].y = 100.0;

    model[2].x = 100.0;
    model[2].y = 100.0;

    model[3].x = 100.0;
    model[3].y = 0.0;

    UAssert(pm.len() == 0);
    pm.setModel(model);

    pos.x = 33;
    pos.y = 66;
    pm.transform(pos);

    points = pm.getSDL_Points();
    UAssert(pm.len_sdl() == 5);
    UAssert(points[0].x == 33);
    UAssert(points[0].y == 66);
    // The Polygon to be drawn should end where it
    // started.
    UAssert(points[4].x == 33);
    UAssert(points[4].y == 66);
}

void register_mob_tests()
{
    URegister(nullptr, nullptr, TSTFUN(test_mob_creation),      "Mob creation");
    URegister(nullptr, nullptr, TSTFUN(test_polymob_creation),  "Poly Mob creation");
    URegister(nullptr, nullptr, TSTFUN(test_polymob_transform), "Poly Mob transform");
}

/* ------------------------ end of file -------------------------------*/
