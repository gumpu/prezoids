#include <SDL.h>
#include "polygons.h"

Polygon::Polygon(int count)
    : m_number_of_points(count), m_points(NULL)
{
    m_points = new SDL_Point[count];
    for (int i = 0; i < m_number_of_points; i++) {
        m_points[i].x = 0;
        m_points[i].y = 0;
    }
}

Polygon::~Polygon()
{
    if (m_points != NULL) {
        delete[] m_points;
    }
}


/* ------------------------ end of file -------------------------------*/
