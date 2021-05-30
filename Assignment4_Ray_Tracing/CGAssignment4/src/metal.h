#ifndef METALH
#define METALH

#include "material.h"

class metal : public material {
public:
    vec3 albedo;
    float fuzz;

    metal(const vec3& a) : albedo(a), fuzz(0.0f) {}

    metal(const vec3& a, float fuzz) : albedo(a) {
        if (fuzz < 1) this->fuzz = fuzz;
        else this->fuzz = 1;
    }

    virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_point());
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};

#endif
