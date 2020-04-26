//
// Created by Dmitry Rybas on 19.04.2020.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hitable.h"

class sphere : public hitable {
public:
    sphere(const vec3& c, float r, std::unique_ptr<material> m)
        : center(c)
        , radius(r)
        , material(std::move(m)) {
    }

    sphere(const sphere&) = delete;
    sphere& operator=(const sphere&) = delete;

    bool hit(const ray& r, float tmin, float tmax, hit_record& hr) const {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            auto result = (-b - sqrt(discriminant)) / (2.0 * a);
            if (tmin < result && tmax > result) {
               hr.t = result;
               hr.p = r.point_at_parameter(result);
               hr.normal = (hr.p - center) / radius;
               return true;
            }

            result = (-b - sqrt(discriminant)) / (2.0 * a);
            if (tmin < result && tmax > result) {
                hr.t = result;
                hr.p = r.point_at_parameter(result);
                hr.normal = (hr.p - center) / radius;
                return true;
            }
        }

        return false;
    }

    vec3 center;
    float radius;
    std::unique_ptr<material> material;
};


#endif //RAYTRACER_SPHERE_H
