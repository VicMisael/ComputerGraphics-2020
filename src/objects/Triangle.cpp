#include "Triangle.hpp"

Triangle::Triangle(Point3f Vertexes[3],Color c)
{
    for (int i = 0; i < 3; i++)
    {
        Vertex[i] = Vertexes[i];
    }
    this->c = c;
}

Triangle::Triangle(Point3f Vertex1, Point3f Vertex2, Point3f Vertex3, Color c)
{
    Vertex[0]=Vertex1;
    Vertex[1]= Vertex2;
    Vertex[2]= Vertex3;
    this->c = c;
}

int Triangle::Intersects(Ray &ray)
{
    using namespace VectorUtilities;
    Vector3f e1 = Vertex[0] - Vertex[1];
    Vector3f e2 = Vertex[0] - Vertex[2];
    Vector3f q = crossProduct(ray.D, e2);
    float a=dotProduct(e1,q);

    Vector3f s = ray.O - Vertex[0];
    Vector3f r = crossProduct(s, e1);
    float weight[3];
    weight[1] = dotProduct(s,q) / a;
    weight[2] = dotProduct(ray.D,r) / a;
    weight[0] = 1.0f - (weight[1] + weight[2]);

    const float dist = dotProduct(e2, r) / a;

    static const float epsilon = 0.0001;;
    static const float epsilon2 = 0.0001;

    if ((a <= epsilon) || (weight[0] < -epsilon2) ||
        (weight[1] < -epsilon2) || (weight[2] < -epsilon2) ||
        (dist <= 0.0f)) {
        // The ray is nearly parallel to the triangle, or the
        // intersection lies outside the triangle or behind
        // the ray origin: "infinite" distance until intersection.
        t_min=INFINITY;
        return 0;
    }
    else {
        t_min = dist;
        return 1;
    }

}

void Triangle::ApplyTransformation()
{
    Vector4f e1 =Vector4f(Vertex[1] - Vertex[0],0);
    Vector4f e2 = Vector4f(Vertex[2] - Vertex[0],0);
    e1=transFMat*e1;
    e2 = transFMat * e2;
    Vector4f mainVertex=Vector4f(Vertex[0], 1);
    mainVertex=transFMat*mainVertex;
    Vertex[0]=mainVertex.toVector3f();
    Vector3f e13f=e1.toVector3f();
    Vector3f e23f = e2.toVector3f();
    Vertex[1] = Vertex[0] + e13f;
    Vertex[2] = Vertex[0] + e23f;
}

