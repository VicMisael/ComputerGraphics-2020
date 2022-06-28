#ifndef _AABB_
#define _AABB_
#include "BaseObject.hpp"
#include "../util/Vector3f.hpp"
class AABB{
private:
    Vector3f vecMin;
    Vector3f vecMax;
public:
    AABB() :AABB(Vector3f(0,0,0),Vector3f(0,0,0)) {};
    AABB(const Vector3f &minV,const Vector3f &maxV){
        this->vecMin=Vector3f(minV.x,minV.y,minV.z);
        this->vecMax=Vector3f(maxV.x,maxV.y,maxV.z);
    };
    int intersects(Ray& ray){
        Vector3f& dir = ray.D;
        Vector3f invdir(1 / dir.x, 1 / dir.y, 1/dir.z);
        float txmin, txmax, tymin, tymax, tzmin, tzmax;
        if (ray.D.x >= 0) {
            txmin = (vecMin.x - ray.O.x) * invdir.x;
            txmax = (vecMax.x - ray.O.x) * invdir.x;
        }
        else {
            txmax = (vecMin.x - ray.O.x) * invdir.x;
            txmin = (vecMax.x - ray.O.x) * invdir.x;
        }
        if (ray.D.y >= 0) {
            tymin = (vecMin.y - ray.O.y) * invdir.y;
            tymax = (vecMax.y - ray.O.y) * invdir.y;
        }
        else {
            tymax = (vecMin.y - ray.O.y) * invdir.y;
            tymin = (vecMax.y - ray.O.y) * invdir.y;
        }
        if ((txmin > tymax) || (tymin > txmax))
            return 0;

        if (tymin > txmin)
            txmin = tymin;

        if (tymax < txmax)
            txmax = tymax;

        tzmax = (vecMin.z - ray.O.z) / ray.D.z;
        tzmin = (vecMax.z - ray.O.z) / ray.D.z;
        if (tzmin > tzmax) 
            std::swap(tzmin, tzmax);

        if ((txmin > tzmax) || (tzmin > txmax))
            return 0;

        if (tzmin > txmin)
            txmin = tzmin;

        if (tzmax < txmax)
            txmax = tzmax;
        return 1;

    };
};
#endif // !_AABB_
