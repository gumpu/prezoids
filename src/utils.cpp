#include <time.h>

double get_hp_time( void )
{
    struct timespec tp;
    (void)clock_gettime( CLOCK_REALTIME, &tp );
    return tp.tv_sec + tp.tv_nsec / 1E9;
}

/* ------------------------ end of file -------------------------------*/
