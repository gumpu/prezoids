#include <cstdlib>
#include <cstdint>
#include "ut.h"

#include <SDL.h>
#include "polygons.h"

static Polygon source_polygon(4);

static void setup()
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

static void test_polygon_translate()
{
    source_polygon.translate(10, 15);
    UAssert(source_polygon[0].x == 10);
    UAssert(source_polygon[0].y == 15);
    UAssert(source_polygon[3].x == 10);
    UAssert(source_polygon[3].y == 115);
}

static void test_polygon_creation()
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

static void test_polygon_copy()
{
    Polygon test_polygon(5);

    /* Perform an operation on the source */
    source_polygon.translate(10, 15);
    UAssert(source_polygon[3].x == 10);
    UAssert(source_polygon[3].y == 115);

    /* Make a copy */
    test_polygon = source_polygon;

    /* Values should match */
    UAssert(test_polygon[3].x == 10);
    UAssert(test_polygon[3].y == 115);
}

void register_polygon_tests()
{
    URegister(nullptr,  nullptr, TSTFUN(test_polygon_creation), "Polygon creation");
    URegister(setup, nullptr, TSTFUN(test_polygon_translate), "Translate Polygon");
    URegister(setup, nullptr, TSTFUN(test_polygon_copy), "Copy Polygon");
}

/* ------------------------ end of file -------------------------------*/
