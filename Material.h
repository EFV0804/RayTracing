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
            attenuation = albedo;
            return true;
        }
        Vec3 albedo;

};
class Metal : public Material
{
    public:
    Metal(const Vec3& a, float fuzziness): albedo(a) { if (fuzziness <1) fuzz = fuzziness; else fuzz = 1;}
    virtual bool scatter(const Ray& rayIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const
    {
        Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz*randomUnitSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    Vec3 albedo;
    float fuzz;
};
class Dielectric : public Material
{
    public:
    Dielectric(float ri): refractionIndex(ri) {}
    virtual bool scatter(const Ray& rayIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const
    {
        Vec3 outwardNormal;
        Vec3 reflected = reflect(rayIn.direction(), rec.normal);
        float niOverNt;
        attenuation = Vec3(1.0,1.0,1.0);
        Vec3 refracted;
        float reflectProb;
        float cosine;

        if(dot(rayIn.direction(), rec.normal) > 0)
        {
            outwardNormal = -rec.normal;
            niOverNt = refractionIndex;
            cosine = refractionIndex * dot(rayIn.direction(), rec.normal)/rayIn.direction().length();
        }
        else
        {
            outwardNormal = rec.normal;
            niOverNt = 1.0 / refractionIndex;
            cosine = -dot(rayIn.direction(), rec.normal)/rayIn.direction().length();
        }
        if (refract(rayIn.direction(), outwardNormal, niOverNt, refracted))
        {
            reflectProb = schlick(cosine, refractionIndex);
        }
        else
        {
            reflectProb = 1.0;
        }
        if (randomDouble() < reflectProb)
        {
            scattered = Ray(rec.p, reflected);
        }
        else
        {
            scattered = Ray(rec.p, refracted);
        }
        return true;
    }
    float refractionIndex;
};
#endif

