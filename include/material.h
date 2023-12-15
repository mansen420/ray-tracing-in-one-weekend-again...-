#ifndef MATERIAL
#define MATERIAL

#include "geometry.h"
#include "global_constants.h"

struct record;

class material
{
public:
    color albedo;
    virtual ~material() = default; 
    //warning : caller must ensure scatteredRay is deleted!
    virtual bool scatter
    (const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const = 0;
};
class diffuse : public material
{
public:
    diffuse(const color& albedo) {this->albedo = albedo;}
    virtual bool scatter
        (const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const override;
};
class metal : public material
{
    float fuzz;
public:
    metal(const color& albedo, float fuzz) {this->albedo = albedo; this->fuzz = fuzz < 1 ? fuzz : 1;}
    virtual bool scatter
        (const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const override;
};
class dialectric : public material
{
    float ir;
public:
    dialectric (float indexOfRefraction) : ir(indexOfRefraction) {albedo = color(1, 1, 1);}
    virtual bool scatter
        (const ray& incidentRay, const record& hitRec, color& attenuation, ray &scatteredRay) const override;
};
float reflectance(float cosine, float ref_idx);
#endif