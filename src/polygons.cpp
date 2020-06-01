#include <cmath>
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

void Polygon::translate(int dx, int dy)
{
    for (int i = 0; i < m_number_of_points; i++) {
        m_points[i].x += dx;
        m_points[i].y += dy;
    }
}

void Polygon::rotate(float angle)
{
    float sa = sin(angle);
    float ca = cos(angle);
    for (int i = 0; i < m_number_of_points; i++) {
        float x, y;
        x = (m_points[i].x * ca) - (m_points[i].y * sa);
        y = (m_points[i].x * sa) + (m_points[i].y * ca);
        m_points[i].x = (int)x;
        m_points[i].y = (int)y;
    }
}

/* ------------------------ end of file -------------------------------*/
