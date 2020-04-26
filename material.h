//
// Created by Dmitry Rybas on 20.04.2020.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "ray.h"
#include "hitable.h"
#include <stdlib.h>

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& hr, vec3& attenuation, ray& scattered) const = 0;
    virtual ~material() { }
};

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class lambertian : public material {
public:
    lambertian(const vec3& albedo_in)
        : albedo(albedo_in) {

    }

    bool scatter(const ray &r_in, const hit_record &hr, vec3 &attenuation, ray &scattered) const {
        vec3 target = hr.p + hr.normal + random_in_unit_sphere();
        scattered = ray(hr.p, target - hr.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};

class metal : public  material {
public:
    metal(const vec3& albedo_in)
            : albedo(albedo_in) {
    }

    bool scatter(const ray& ray_in, const hit_record& hr, vec3& attenuation, ray& scattered) const {

        return false;
    }

    vec3 albedo;
};

#endif //RAYTRACER_MATERIAL_H
