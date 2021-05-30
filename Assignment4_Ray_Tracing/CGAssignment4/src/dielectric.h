#ifndef DIELECTRICH
#define DIELECTRICH

#include "ray.h"
#include "material.h"

float schlick(float cosine, float ri) {
    float r0 = (1 - ri) / (1 + ri);
    r0 *= r0;
    return r0 + (1 - r0) * pow(1 - cosine, 5);
}

class dielectric : public material {
public:
    float ri;

    dielectric(float ri) : ri(ri) {}
    virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal, refracted;
        vec3 reflected = reflect(ray_in.direction(), rec.normal);
        float ni_over_nt, cosine, reflect_prob;
        attenuation = vec3(1.0, 1.0, 1.0);
        if (dot(ray_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ri;
            cosine = ri * dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
        }
        else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ri;
            cosine = -dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
        }

        if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted)) {
            scattered = ray(rec.p, refracted);
            reflect_prob = schlick(cosine, ri);
        }
        else {
            reflect_prob = 1.0f;
        }

        if (drand48() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        }
        else {
            scattered = ray(rec.p, refracted);
        }
        
        return true;
    }
};

#endif // !DIELECTRICH
