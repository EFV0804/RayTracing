cmake_minimum_required(VERSION 3.15)
project(RayTracing)
set(CMAKE_CXX_STANDARD 14)
add_executable(RayTracing main.cpp Vec3.h Ray.h Hittable.h HittableList.h Random.h Sphere.h Camera.h)
