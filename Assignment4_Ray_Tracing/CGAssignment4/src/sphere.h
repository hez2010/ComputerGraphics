#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere : public hitable {
public:
    vec3 center;
    float radius;
    material* mat_ptr;

    sphere(vec3 center, float radius, material* mat_ptr) : center(center), radius(radius), mat_ptr(mat_ptr){}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        vec3 oc = r.origin() - center;
        float a = dot(r.direction(), r.direction());
        float b = dot(oc, r.direction());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0) {
            float temp1 = (-b - sqrt(discriminant)) / a, temp2 = (-b + sqrt(discriminant)) / a;
            float temp;
            bool h = false;

            if (temp1 < t_max && temp1 > t_min) {
                temp = temp1;
                h = true;
            }
            else if (temp2 < t_max && temp2 > t_min) {
                temp = temp2;
                h = true;
            }

            if (h) {
                rec.t = temp;
                rec.p = r.point(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.material = mat_ptr;
                return true;
            }
        }

        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb& box) const {
        box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
        return true;
    }
};

#endif