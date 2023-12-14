#include "vec3.h"

struct ray
{   //rays are immutable
    ray (const point &origin, const vec3 &direction) : rayOrigin(origin), rayDirection(direction) {}
    const point rayOrigin;
    const vec3 rayDirection;
    point at(float t)
    {
        return rayOrigin + t * rayDirection;
    } 
};