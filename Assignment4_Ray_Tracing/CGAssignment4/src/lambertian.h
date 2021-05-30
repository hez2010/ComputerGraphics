#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.h"

class lambertian : public material {
public:
    vec3 albedo;

    lambertian(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_point();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

#endif