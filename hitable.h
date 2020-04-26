//
// Created by Dmitry Rybas on 19.04.2020.
//

#ifndef RAYTRACER_HITABLE_H
#define RAYTRACER_HITABLE_H

#include "ray.h"

class material;

struct hit_record {
   float t;
   vec3 normal;
   vec3 p;
   material* material = nullptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& hr) const = 0;
    virtual ~hitable() = default;
};

#endif //RAYTRACER_HITABLE_H
