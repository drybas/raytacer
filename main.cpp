#include <iostream>
#include <limits>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

float hit_spehere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1;
    else
        return (-b - sqrt(discriminant)) / (2.0 * a);
}

vec3 color(const ray& r) {
    auto t = hit_spehere(vec3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
        return 0.5 * vec3(N.x() /*+ 1*/, N.y() /*+ 1*/, N.z() /*+ 1*/);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

vec3 color(const ray& r, const hitable& world) {
    hit_record hr;
    if (world.hit(r, 0.0001, std::numeric_limits<float>::max(), hr)) {
        // version with basic reflection
        vec3 target = hr.p + hr.normal + random_in_unit_sphere();
        return 0.5 * color(ray(hr.p, target - hr.p), world);

        // simple version
        //return 0.5 * vec3(hr.normal.x() + 1, hr.normal.y() + 1, hr.normal.z() + 1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

vec3 color(const ray& r, const hitable& world, int depth) {
    hit_record hr;
    if (world.hit(r, 0.0001, std::numeric_limits<float>::max(), hr)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && hr.material->scatter(r, hr, attenuation, scattered)) {
            return vec3(0, 0, 0);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 150;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable_list world;
    world.objects.emplace_back(std::make_unique<sphere>(vec3(0, 0.0, -5.0), 0.33,
            std::make_unique<lambertian>(vec3(0.8, 0.3, 0.3))));
  //  world.objects.emplace_back(std::make_unique<sphere>(vec3(-1, 0.0, -1.0), 0.2));
   // world.objects.emplace_back(std::make_unique<sphere>(vec3(0, -100.5, -1), 100));
    camera cam;
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                auto u = float(i + drand48()) / float(nx);
                auto v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
