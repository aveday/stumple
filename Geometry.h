#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define MAX_VERTICES 8


struct IVec2 {
    int x, y;
    IVec2(int x, int y): x(x), y(y) { }
    IVec2 operator+ (const IVec2&);
    void operator+= (const IVec2&);
    IVec2 operator* (int);
};

struct Vec2 {
    double x, y;
    double getLength();
    void rotate(double a);
    Vec2(double x, double y): x(x), y(y) { }
    Vec2 operator+ (const Vec2&);
    void operator+= (const Vec2&);
	void operator+= (const IVec2&);
    Vec2 operator* (double);
};

struct Grid {
    int size;
    uint32_t color;
    uint32_t background;
    Grid(int s, uint32_t c, uint32_t bg):
        size(s), color(c), background(bg) { }
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

#endif
