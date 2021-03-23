#ifndef _RAY_
#define _RAY_
#include "Vector3f.hpp"
#include "Vector4f.hpp"
class Ray
{
public:
    Point3f O;
    float t; // Onde o raio intercepta o objeto;
    Vector3f D;
    Ray(Point3f vec, Point3f Eye);
    Vector4f getOriginInPoint4f();
    Vector4f getDirectionInVector4f();
};

#endif