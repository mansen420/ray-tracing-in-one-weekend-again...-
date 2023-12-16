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

bool dialectric::scatter(const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const
{
    attenuation = albedo;
    float refraction_ratio = hitRec.intersected_outside ? (1.0/ir) : ir;

    vec3 unitDirection = normalized(incidentRay.direction);

    double cos_theta = fmin(dot(-unitDirection, hitRec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    vec3 scatterDirection;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_f())
        scatterDirection = reflect(unitDirection, hitRec.normal);
    else
        scatterDirection = refract(unitDirection, hitRec.normal, refraction_ratio);

    scatteredRay = ray(hitRec.p, scatterDirection);

    return true;
}
float reflectance(float cosine, float ref_idx) 
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
bool light::scatter (const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const
{
    attenuation = albedo;
    return true;   
}