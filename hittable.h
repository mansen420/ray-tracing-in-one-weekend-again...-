#ifndef HITTABLE
#define HITTABLE

#include "ray.h"

struct record
{
    point p;
    float t;
    vec3 normal;
};
class hittable 
{
public:
    virtual ~hittable() = default;  //whad does this do?
    virtual bool intersect(const ray &r, const float tMin,const float tMax, record &hitRecord) const = 0;
};

#endif