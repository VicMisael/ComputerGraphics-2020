#ifndef _TRIANGLE_
#define _TRIANGLE_
#include "BaseObject.hpp"
#include "../util/VectorUtilities.hpp"
class Triangle : public BaseObject
{
private:
    Point3f Vertex[3];

public:
    Triangle() : Triangle(Point3f(0, 0, 0), Point3f(0, 0, 0), Point3f(0, 0, 0)) {}
    Triangle(Point3f Vertexes[3], Color c);
    Triangle(const Point3f Vertex1, const Point3f Vertex2, const Point3f Vertex3, const Color c);
    Triangle(const Point3f Vertex1, const Point3f Vertex2, const Point3f Vertex3) : Triangle(Vertex1, Vertex2, Vertex3, Color(0, 0, 0)){};
    int Intersects(Ray &ray);
    void ApplyTransformation();
    Vector3f getNormal(const Point3f p) override;
};
#endif