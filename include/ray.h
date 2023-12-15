#ifndef RAY 
#define RAY

#include "vec3.h"

struct ray
{
    ray (const point &origin, const vec3 &direction) : origin(origin), direction(direction) {}
    ray () {}
    point origin;
    vec3 direction;
    point at(float t) const
    {
        return origin + t * direction;
    }
};

#endif