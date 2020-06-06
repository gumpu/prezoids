#ifndef HG_POLYGONS_H
#define HG_POLYGONS_H

class Polygon {
    public:
        Polygon() = delete;
        Polygon(int count);
        ~Polygon();
        Polygon(const Polygon& source);
        Polygon& operator=(const Polygon& source);
        SDL_Point& operator[] (int i);
        int len(void) { return m_number_of_points; }
        int capacity(void) { return m_capacity; }
        const SDL_Point* points(void) { return m_points; }

        void translate(int dx, int dy);
        void rotate(float angle);
        SDL_Point center(void);

    private:
        int m_capacity;
        int m_number_of_points;
        SDL_Point* m_points;
};

#endif /* HG_POLYGONS_H */
