#ifndef GEOMETRY_H
#define GEOMETRY_H

#define MAX_VERTICES 6

struct Vec2 {
    double x, y;
	float getLength();
	void add(Vec2);
};

struct Polygon {
    Vec2 vertices[MAX_VERTICES];
    int vertexCount;
};


float normalizeAngle(float a);
void printVec2(Vec2);
void rotateVec2(Vec2* v, float da);

#endif
