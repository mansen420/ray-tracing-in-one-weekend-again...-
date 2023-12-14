#include "geometry.h"
#include <cmath>

bool sphere::intersect(const ray &r, const float tMin,const float tMax, record &hitRecord) const
{
    const vec3 &oc = r.origin-this->c;
    const float &b = 2*dot(r.direction, oc);
    const float &a = r.direction.magnitudeSquared();
    const float &c = oc.magnitudeSquared()-(this->r*this->r);
    const float &discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return false;
    float root = (-b - sqrt(discriminant))/(2.0*a);
    if (root >= tMax || root <= tMin)
    {
        root = (-b + sqrt(discriminant))/(2.0*a);
        if (root >= tMax || root <= tMin)
            return false;
    } 
    hitRecord.t = root;
    hitRecord.p = r.at(root);
    hitRecord.setNormal(r.direction , normalized((hitRecord.p - this->c)/this->r));
    
    return true;
}