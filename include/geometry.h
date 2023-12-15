#ifndef GEOMETRY
#define GEOMETRY

#include "ray.h"
#include "interval.h"

struct record
{
    point p;
    float t;
    bool intersected_outside;
    void setNormal(const vec3 &intersectDirection, const vec3 &outwardNormal)
    {   //assumes outward normal is unit length!
        intersected_outside = dot(intersectDirection, outwardNormal) < 0; 
        normal = intersected_outside ? outwardNormal : -outwardNormal;
    }
    vec3 normal;    //this normal is agianst the intersection direction
};
class hittable 
{
public:
    virtual ~hittable() = default;  //whad does this do?
    virtual bool intersect(const ray &r, const interval &intersectionRange, record &hitRecord) const = 0;
};

class sphere : public hittable
{
    float r;
    point c;
public:
    sphere(point center, float radius) : r(radius), c(center) {}
    virtual bool intersect(const ray &r, const interval &intersectionRange, record &hitRecord) const override;
};

#endif