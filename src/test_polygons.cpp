#include <cstdlib>
#include <cstdint>
#include "ut.h"

#include <SDL.h>
#include "polygons.h"

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
}

/* ------------------------ end of file -------------------------------*/
