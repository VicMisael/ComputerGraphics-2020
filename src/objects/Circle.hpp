#ifndef _CIRCLE_
#define _CIRCLE_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "AABB.h"
#include "BaseObject.hpp"
class Circle : public BaseObject
{
private:
    AABB aabb;
    float radius;
    Point3f Center;
public:
    Circle(float radius,const Color c);  
    int Intersects(Ray& ray) override;
    void ApplyTransformation() override;
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 m) override;
    void computeAABB();
};
#endif