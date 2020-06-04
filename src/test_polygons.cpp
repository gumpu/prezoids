#include <cstdlib>
#include <cstdint>
#include "ut.h"

#include <SDL.h>
#include "polygons.h"

Polygon source_polygon(4);

static void setup(void)
{
    source_polygon[0].x = 0;
    source_polygon[0].y = 0;
    source_polygon[1].x = 100;
    source_polygon[1].y = 0;
    source_polygon[2].x = 100;
    source_polygon[2].y = 100;
    source_polygon[3].x = 0;
    source_polygon[3].y = 100;
}

void test_polygon_translate(void)
{
    source_polygon.translate(10, 15);
    UAssert(source_polygon[0].x == 10);
    UAssert(source_polygon[0].y == 15);
    UAssert(source_polygon[3].x == 10);
    UAssert(source_polygon[3].y == 115);
}

void test_polygon_creation(void)
{
    Polygon test_polygon(5);

    UAssert(test_polygon[0].x == 0);
    UAssert(test_polygon[4].x == 0);

    test_polygon[4].x = 40;
    test_polygon[4].y = 50;

    UAssert(test_polygon[4].x == 40);
    UAssert(test_polygon[0].x == 0);
    UAssert(test_polygon[4].y == 50);

    UAssert(test_polygon.len() == 5);
}

void register_polygon_tests(void)
{
    URegister(NULL,  NULL, TSTFUN(test_polygon_creation), "Polygon creation");
    URegister(setup, NULL, TSTFUN(test_polygon_translate), "Translate Polygon");
}

/* ------------------------ end of file -------------------------------*/
