#ifndef GEOMETRY_H
#define GEOMETRY_H

#define MAX_VERTICES 8

struct IVec2 {
    int x, y;
    IVec2(int x, int y): x(x), y(y) { }
    IVec2 operator+ (const IVec2&);
    IVec2 operator* (int);
};

struct Vec2 {
    double x, y;
    double getLength();
    Vec2(double x, double y): x(x), y(y) { }
    Vec2 operator+ (const Vec2&);
    void operator+= (const Vec2&);
    Vec2 operator* (double);
};

struct Grid {
    int size;
    Grid(int s): size(s) { }
    Vec2 GetScreenPosition(IVec2);
};

class Polygon {
    public:
        Vec2 *vertices[MAX_VERTICES];
        int vertexCount;
        Polygon(int, double, double);
};

double normalizeAngle(double a);
void printVec2(Vec2);
void rotateVec2(Vec2* v, double da);

#endif
