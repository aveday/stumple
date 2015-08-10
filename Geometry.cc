
#include <iostream>
#include <math.h>

#include "Geometry.h"

void printVec2(Vec2 v) {
    std::cout << v.x << ", " << v.y << std::endl;
}

float normalizeAngle(float a) {
    if( a > M_PI )
        return a - M_2_PI;
    else if( a < -M_PI )
        return a + M_2_PI;
    else
        return a;
}

void rotateVec2(Vec2* v, float da) {
    float a;
    if( v->x == 0 ) {
        a = M_PI/2.0;
        if( v->y < 0 )
            a -= M_PI;
    } else {
        a = atan(v->y/v->x);
        if( v->x < 0 )
            a += M_PI;
    }
    float h = v->getLength();
    v->x = h*cos(a+da);
    v->y = h*sin(a+da);
}


float Vec2::getLength() {
	return sqrt( pow(x, 2) + pow(y, 2) );
}

void Vec2::add(Vec2 v) {
	x += v.x;
	y += v.y;
}
