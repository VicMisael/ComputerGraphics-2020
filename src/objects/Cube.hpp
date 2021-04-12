#ifndef _CUBE_
#define _CUBE_
#include "../util/Vector3f.hpp"
#include "BaseObject.hpp"
#include "Triangle.hpp"

class Cube : public BaseObject
{
    Point3f face[4];
    Point3f face2[4];
    Triangle triangles[12];
    void CalculateTriangles();
public:
    Cube(float height, float width, float depth, Color c);
    int Intersects(Ray &ray);
    void ApplyTransformation();
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 mm) override;
};

#endif