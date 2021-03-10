#ifndef MATERIALH
#define MATERIALH
#include "Hittable.h"
//#include "Ray.h"
//#include "Vec3.h"

//struct hitRecord;

class Material
{
public:
    virtual bool scatter(const Ray& rayIn, const hitRecord& record, Vec3& attenuation, Ray& scattered) const = 0;
};
class Lambert: public Material{
    public:
        Lambert(const Vec3& a): albedo(a) {}
        virtual bool scatter(const Ray& rayIn, const hitRecord& record, Vec3& attenuation, Ray& scattered) const {
            Vec3 target = record.p + record.normal + randomUnitSphere();
            scattered = Ray(record.p, target-record.p);
            attenuation - albedo;
            return true;
        }
        Vec3 albedo;

};
#endif

