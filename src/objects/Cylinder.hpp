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
        Color  BaseColor;
        bool baseIntersected=false;
    public:
        Cylinder(Vector3f axis, float height, float radius, const Color color) :Cylinder(axis, height, radius, color, color) {};
        Cylinder(Vector3f axis, float height, float radius,const Color color,const Color BaseColor);
        int Intersects(Ray& ray);
        Color getColor() override;
        void ApplyTransformation();
        Vector3f getNormal(const Point3f p);
        void ApplyCamera(const Matrix4x4 m);
};

#endif