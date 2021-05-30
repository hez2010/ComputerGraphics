#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "material.h"
#include "aabb.h"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material* material;
};

class hitable {
public:
    virtual bool hit(const ray& t, float t_min, float t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

#endif