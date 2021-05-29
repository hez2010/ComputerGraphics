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
};

#endif