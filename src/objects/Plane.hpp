#ifndef _PLANE_
#define _PLANE_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"

class Plane : public BaseObject
{
private: 
    Vector3f n;
    Point3f pplane;
public:
    Plane(Vector3f u,Point3f kp, Color c);

    int Intersects(Ray& ray);
    void ApplyTransformation();
    Vector3f getNormal(const Point3f p) override;
};

#endif