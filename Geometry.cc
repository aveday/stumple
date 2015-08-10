
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Geometry.h"

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

void rotateVec2(Vec2* v, double da) {
    double a;
    if( v->x == 0 ) {
        a = M_PI/2.0;
        if( v->y < 0 )
            a -= M_PI;
    } else {
        a = atan(v->y/v->x);
        if( v->x < 0 )
            a += M_PI;
    }
    double h = v->getLength();
    v->x = h*cos(a+da);
    v->y = h*sin(a+da);
}


double Vec2::getLength() {
    return sqrt( pow(x, 2) + pow(y, 2) );
}

void Vec2::add(Vec2 v) {
    x += v.x;
    y += v.y;
}

Polygon::Polygon(int sides, double sideLength, double rotation) {
	if(sides > MAX_VERTICES) {
		 exit(EXIT_FAILURE);
		 fprintf(stderr, "Polygon had too many sides!\n");
	}


	double angle = M_PI_2 - M_PI/sides + rotation;
	double increment = 2*M_PI/sides;
	double radius = sideLength / (2*sin(increment/2));

    for(int i = 0; i < sides; i++, angle += increment)
        vertices[i] = new Vec2(radius * cos(angle), radius * sin(angle));


    //double internalAngle = M_PI - 2*M_PI/sides;
    //double radius = sideLength / (2*sin(M_PI/sides));
    vertexCount = sides;
    //double angle = rotation + M_PI/sides - M_PI_2;
    //for(int i = 0; i < sides ; i++, angle += M_PI - 2*M_PI/sides) {

}

