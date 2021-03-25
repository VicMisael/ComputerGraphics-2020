#ifndef _TRIANGLE_
#define _TRIANGLE_
#include "BaseObject.hpp"
class Triangle{
    private:
    Point3f Vertex[3];
    public:
    int Intersects(Ray& ray);
    void ApplyTransformation();
};
#endif