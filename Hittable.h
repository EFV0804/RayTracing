#ifndef HITTABLEH
#define HITTABLEH
#include "Ray.h"

class Material;

struct hitRecord
{
    float t;
    Vec3 p;
    Vec3 normal;
    std::shared_ptr<Material> matPtr;
};
class Hittable
{
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const = 0;
};

#endif