#ifndef _TRIANGLE_
#define _TRIANGLE_
#include "BaseObject.hpp"
#include "../util/VectorUtilities.hpp"
class Triangle:public BaseObject{
    private:
    Point3f Vertex[3];
    public:
    Triangle(Point3f Vertexes[3],Color c);
    Triangle(Point3f Vertex1, Point3f Vertex2, Point3f Vertex3, Color c);
    int Intersects(Ray& ray);
    void ApplyTransformation();
};
#endif