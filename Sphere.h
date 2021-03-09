#ifndef SPHEREH
#define SPHEREH
#include "Hittable.h"

class Sphere: public Hittable
{
public:
    Sphere() {}
    Sphere(Vec3 cen, float r): center(cen), radius(r) {};
    virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;
    Vec3 center;
    float radius;
};

bool Sphere::hit(const Ray&r, float tMin, float tMax, hitRecord& record) const
{
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction()); //length of ray
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0)
    {
        float temp = (-b -sqrt(discriminant))/ a;
        if(temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = r.pointAtParameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
        temp = (-b +sqrt(discriminant))/ a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = r.pointAtParameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif