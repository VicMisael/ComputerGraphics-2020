#ifndef _PLANE_
#define _PLANE_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"

class Plane final : public BaseObject
{
private: 
    Vector3f n;
    Point3f pplane;
public:
    Plane(Vector3f u,Point3f kp, Color c);
    std::tuple<int, float, Vector3f> Intersects(const Ray& ray) final override;
    void ApplyTransformation() override;
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 m) override;
};

#endif