#include <cstdlib>
#include <cstdint>
#include "ut.h"

void test_tile_1(void)
{

}

void register_tiles_tests(void)
{
    URegister(NULL,  NULL, TSTFUN(test_tile_1), "hello world");
}

/* ------------------------ end of file -------------------------------*/
