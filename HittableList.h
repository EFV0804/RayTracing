#ifndef HITTABLELISTH
#define HITTABLELISTH

#include"Hittable.h"

class HittableList: public Hittable
{
public:
    HittableList() {}
    HittableList(Hittable **l, int n) {list = l; listSize = n;}
    virtual bool hit( const Ray& r, float tMin, float tMax, hitRecord& record) const;
    Hittable **list;
    int listSize;
};

bool HittableList::hit(const Ray& r, float tMin, float tMax, hitRecord& record) const
{
    hitRecord tempRecord;
    bool hitAnything = false;
    double closestT = tMax;
    for (int i = 0; i < listSize; i++)
    {
        if(list[i]->hit(r, tMin, closestT, tempRecord))
        {
            hitAnything = true;
            closestT = tempRecord.t;
            record = tempRecord;
        }
    }
    return hitAnything;
}
#endif