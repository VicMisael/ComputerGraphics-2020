#ifndef _CUBE_
#define _CUBE_
#include "../util/Vector3f.hpp"
#include "BaseObject.hpp"
#include "Triangle.hpp"
#include "AABB.h"
#include <vector>

class Cube final : public BaseObject
{
    Point3f face[4];
    Point3f face2[4];
    Triangle triangles[12];
    AABB aabb;
    //std::vector<Triangle> triangles;
    Vector3f Normal;
    void CalculateTriangles();
 
 
public:
    Cube(float height, float width, float depth, Color c);
 
    std::tuple<int, float, Vector3f> Intersects(const Ray &ray) final override;
    void ApplyTransformation() override;
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 mm) override;
    void computeAABB();
};


#endif