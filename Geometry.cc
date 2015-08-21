
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Geometry.h"

Rect::Rect(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void printVec2(Vec2 v) {
    printf("%f, %f\n", v.x, v.y);
}

double normalizeAngle(double a) {
    if( a > 2*M_PI )
        return a - 2*M_PI;
    else if( a < 0 )
        return a + 2*M_PI;
    else
        return a;
}

void Vec2::rotate(double da) {
    double a;
    if( x == 0 ) {
        a = M_PI/2.0;
        if( y < 0 )
            a -= M_PI;
    } else {
        a = atan(y/x);
        if( x < 0 )
            a += M_PI;
    }
    double h = getLength();
    x = h*cos(a+da);
    y = h*sin(a+da);
}

double Vec2::getLength() {
    return sqrt( pow(x, 2) + pow(y, 2) );
}

IVec2 IVec2::operator+ (const IVec2 &v) {
    return IVec2(x + v.x, y + v.y);
}

void IVec2::operator+= (const IVec2 &v) {
	x += v.x;
	y += v.y;
}

IVec2 IVec2::operator* (int i) {
    return IVec2(x * i, y * i);
}

Vec2 Vec2::operator+ (const Vec2 &v) {
    return Vec2(x + v.x, y + v.y);
}

void Vec2::operator+= (const Vec2 &v) {
	x += v.x;
	y += v.y;
}

void Vec2::operator+= (const IVec2 &v) {
	x += v.x;
	y += v.y;
}

Vec2 Vec2::operator* (double i) {
    return Vec2(x * i, y * i);
}

Polygon::Polygon(int sides, double sideLength, double rotation) {
    if(sides > MAX_VERTICES) {
         fprintf(stderr, "Polygon had too many sides!\n");
         exit(EXIT_FAILURE);
    }

    vertexCount = sides;

    double angle = M_PI_2 - M_PI/sides + rotation;
    double increment = 2*M_PI/sides;
    double radius = sideLength / (2*sin(increment/2));

    for(int i = 0; i < sides; i++, angle += increment)
        vertices[i] = new Vec2(radius * cos(angle), radius * sin(angle));
}
