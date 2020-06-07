#ifndef HG_POLYGONS_H
#define HG_POLYGONS_H

class FLT_Point {
    public:
        float x;
        float y;
};

class Polygon {
    public:
        Polygon() = delete;
        Polygon(int count);
        ~Polygon();
        Polygon(const Polygon& source);
        Polygon& operator=(const Polygon& source);
        FLT_Point& operator[] (int i);
        int len(void) { return m_number_of_points; }
        int capacity(void) { return m_capacity; }
        const FLT_Point* points(void) { return m_points; }

        void translate(float dx, float dy);
        void rotate(float angle);
        FLT_Point center(void);

    private:
        int m_capacity;
        int m_number_of_points;
        FLT_Point* m_points;
};

#endif /* HG_POLYGONS_H */
