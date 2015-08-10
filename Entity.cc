#include <stdint.h>

#include "Geometry.h"
#include "Entity.h"

Entity::Entity(Vec2 p, Polygon s, uint32_t c):
	position(p), shape(s), color(c) {
}
