#ifndef _TRIANGLE_
#define _TRIANGLE_
#include "BaseObject.hpp"
#include "../util/VectorUtilities.hpp"
class Triangle : public BaseObject
{
private:
    
    Vector3f Normal;
    void CalculateNormal();
public:
    Point3f Vertex[3];
    Triangle() : Triangle(Point3f(0, 0, 0), Point3f(0, 0, 0), Point3f(0, 0, 0)) {}
    Triangle(Point3f Vertexes[3], Color c);
    Triangle(const Point3f Vertex1, const Point3f Vertex2, const Point3f Vertex3, const Color c);
    Triangle(const Point3f Vertex1, const Point3f Vertex2, const Point3f Vertex3) : Triangle(Vertex1, Vertex2, Vertex3, Color()){};
    int Intersects(Ray &ray) override;
    void ApplyTransformation() override;
    Vector3f getNormal(const Point3f p) override;
    void ApplyCamera(const Matrix4x4 m) override;
};
#endif