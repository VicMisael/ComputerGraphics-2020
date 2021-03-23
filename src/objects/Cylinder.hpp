#ifndef _CYLINDER_
#define _CYLINDER_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "BaseObject.hpp"

class Cylinder : public BaseObject
{
    private: // center of cylinder 
    Vector3f axis; // cylinder axis 
    Point3f Base;
    float height;
    float radius;
    public:
     
    Cylinder(Vector3f axis, float height, float radius,Color color);
    int Intersects(Ray& ray);
    void ApplyTransformation();
};

#endif