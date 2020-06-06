#include <cmath>
#include <SDL.h>
#include "polygons.h"

Polygon::Polygon(int count)
    : m_capacity(count), m_number_of_points(0), m_points(NULL)
{
    m_points = new SDL_Point[count];
    for (int i = 0; i < m_capacity; i++) {
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

SDL_Point& Polygon::operator[] (int i)
{
    if ((i+1) > m_number_of_points) {
        m_number_of_points = i + 1;
    }
    return m_points[i];
}

void Polygon::translate(int dx, int dy)
{
    for (int i = 0; i < m_number_of_points; i++) {
        m_points[i].x += dx;
        m_points[i].y += dy;
    }
}

SDL_Point Polygon::center(void)
{
    SDL_Point p;
    float xs = 0.0;
    float ys = 0.0;
    for (int i = 0; i < m_number_of_points; i++) {
        xs += m_points[i].x;
        ys += m_points[i].y;
    }
    p.x = int(xs/m_number_of_points);
    p.y = int(ys/m_number_of_points);
    return p;
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

Polygon& Polygon::operator=(const Polygon& source)
{
    int i;
    for (i = 0; i < source.m_number_of_points; ++i) {
        m_points[i].x = source.m_points[i].x;
        m_points[i].y = source.m_points[i].y;
    }
    return *this;
}

/* ------------------------ end of file -------------------------------*/
