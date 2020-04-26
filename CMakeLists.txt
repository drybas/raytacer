cmake_minimum_required(VERSION 3.15)
project(raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(raytracer main.cpp vec3.h ray.h hitable.h sphere.cpp sphere.h hitable_list.h camera.h material.h lamertian.h)