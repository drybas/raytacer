//
// Created by Dmitry Rybas on 19.04.2020.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <math.h>

class vec3 {
public:
    vec3() {}
    vec3(float e0, float e1, float e2) {
       e[0] = e0;
       e[1] = e1;
       e[2] = e2;
    }

    auto x() const { return e[0]; }
    auto y() const { return e[1]; }
    auto z() const { return e[2]; }

    float operator [] (int index) const {
        return e[index];
    }

    vec3& operator += (const vec3& v) {
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }

    vec3& operator /=(float p) {
        e[0] /= p;
        e[1] /= p;
        e[2] /= p;
        return *this;
    }

    float squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

private:
   float e[3];
};

vec3 operator + (const vec3& v0, const vec3& v1) {
    return vec3(v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2]);
}

vec3 operator - (const vec3& v0, const vec3& v1) {
    return vec3(v0[0] - v1[0], v0[1] - v1[1], v0[2]- v1[2]);
}

vec3 operator - (const vec3& v0, float p) {
    return vec3(v0[0] - p, v0[1] - p, v0[2] - p);
}

vec3 operator * (float p, const vec3& v) {
    return vec3(v[0] * p, v[1] * p, v[2] * p);
}

vec3 operator * (const vec3& v0, const vec3& v1) {
    return vec3(v0[0] * v1[0], v0[1] * v1[1], v0[2] * v1[2]);
}

float dot(const vec3& v0, const vec3& v1) {
    return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

vec3 operator / (const vec3& v, float p) {
    return vec3(v[0] / p, v[1] / p, v[2] / p);
}

vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif //RAYTRACER_VEC3_H
