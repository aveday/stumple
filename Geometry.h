#ifndef GEOMETRY_H
#define GEOMETRY_H

#define MAX_VERTICES 8

struct Vec2 {
    double x, y;
    double getLength();
    void add(Vec2);
    Vec2(double x, double y): x(x), y(y) { }
};

struct IVec2 {
	int x, y;
	IVec2(int x, int y): x(x), y(y) { }
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
