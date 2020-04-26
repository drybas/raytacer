//
// Created by Dmitry Rybas on 19.04.2020.
//
#include "hitable.h"
#include <vector>
#include <memory>

class hitable_list : public hitable {
public:
    bool hit(const ray &r, float tmin, float tmax, hit_record &hr) const override {
        bool hit = false;
        float t = tmax;
        hit_record tmp;
        for (auto &i: objects) {
            if (i->hit(r, tmin, t, tmp)) {
                hit = true;
                t = tmp.t;
                hr = tmp;

            }
        }

       return hit;
    }
    std::vector<std::unique_ptr<hitable>> objects;
};
