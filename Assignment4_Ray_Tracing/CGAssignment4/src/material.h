#ifndef MATERIALH
#define MATERIALH

#include "hitable.h"
struct hit_record;

class material {
public:
    virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif