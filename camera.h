//
// Created by Dmitry Rybas on 20.04.2020.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera()
        : lower_left_corner(-2.0, -1.0, -1.0 )
        , hor(4.0, 0.0, 0.0)
        , vert(0.0, 2.0, 0.0)
        , origin(0.0, 0.0, 0.0) {
    }

    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner + u * hor + v * vert);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 hor;
    vec3 vert;
};

#endif //RAYTRACER_CAMERA_H
