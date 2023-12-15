#include "../include/material.h"
#include <cmath>
bool diffuse::scatter(const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const
{
    vec3 scatterDirection = hitRec.normal + random_on_unit_sphere();
    if (fabs(scatterDirection.x) < 1e-8 && fabs(scatterDirection.y) < 1e-8 && fabs(scatterDirection.z) < 1e-8)
        scatterDirection = hitRec.normal;
    scatteredRay = ray(hitRec.p, scatterDirection);
    attenuation = albedo;
    return true;    
}
bool metal::scatter(const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const
{
    scatteredRay = ray(hitRec.p, reflect(normalized(incidentRay.direction), hitRec.normal) + fuzz * random_on_unit_sphere());
    attenuation = albedo;
    return dot(scatteredRay.direction, hitRec.normal) > 0;
}