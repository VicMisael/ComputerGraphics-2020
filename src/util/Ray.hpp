#ifndef _RAY_
#define _RAY_
#include "Vector3f.hpp"
#include "Vector4f.hpp"
class Ray
{
public:
    Point3f O;
    float t;
    Vector3f D;
    Ray(Point3f vec, Point3f Eye);
};
#endif