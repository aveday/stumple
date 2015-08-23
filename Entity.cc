#include <stdint.h>

#include "Entity.h"


Entity::Entity(b2Body* b, int d):
		body(b), depth(d) {
}
