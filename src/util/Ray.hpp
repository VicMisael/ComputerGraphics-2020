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
    Ray(Point3f point, Point3f eye) :Ray(point, point - eye, 1) {};
    Ray(Point3f point, Vector3f D,float t);
    Point3f getPoint(float t);
    Vector4f getOriginInPoint4f();
    Vector4f getDirectionInVector4f();
};

#endif