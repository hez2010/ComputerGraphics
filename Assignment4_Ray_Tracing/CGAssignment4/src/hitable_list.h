#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable {
public:
    hitable** list;
    int size;

    hitable_list() {}
    hitable_list(hitable **list, int size) : list(list), size(size) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        hit_record temp_rec;
        bool h = false;
        double closest = t_max;

        for (int i = 0; i < size; i++) {
            if (list[i]->hit(r, t_min, closest, temp_rec)) {
                h = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }

        return h;
    }

    virtual bool bounding_box(float t0, float t1, aabb& box) const {
        if (size < 1) return false;

        aabb temp_box;
        bool first_true = list[0]->bounding_box(t0, t1, temp_box);
        if (!first_true) return false;
        box = temp_box;
        for (int i = 1; i < size; i++) {
            if (list[i]->bounding_box(t0, t1, temp_box)) {
                box = surrounding_box(box, temp_box);
            }
            else return false;
        }

        return true;
    }
};

#endif