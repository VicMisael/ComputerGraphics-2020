#include "Cone.hpp"
#include <vector>
#include "Plane.hpp"

Cone::Cone(Point3f vertice, Vector3f axis, float height, float radius, Color c)
{
    this->center = Point3f(0, 0, 0);
    // Eixo que aponta para o topo do cone.
    this->vertice = vertice;
    this->axis = axis;
    this->height = height;
    this->radius = radius;
    this->c = c;
    this->axis.normalize();
}

int Cone::Intersects(Ray &ray)
{
    float t_min = -INFINITY;
    Point3f Po = ray.O;

    Vector3f d = ray.D;
    Vector3f n = axis;
    Vector3f v = vertice - Po;

    float cosTheta = height / (sqrtf(height * height + radius + radius));
    using namespace VectorUtilities;
    using namespace std;
    float a = pow(dotProduct(d, n), 2) - dotProduct(d, d) * powf(cosTheta, 2);
    float b = dotProduct(v, d) * powf(cosTheta, 2) - dotProduct(v, n) * dotProduct(d, n);
    float c = pow(dotProduct(v, n), 2) - dotProduct(v, v) * powf(cosTheta, 2);
    float delta = b * b - (a * c);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    if (delta < 0)
    {
        return 0;
    }
    return 1;
}

void Cone::ApplyTransformation()
{
    Point4f base4(center, 1);
    base4 = transFMat * base4;
    Vector4f axis4(axis, 0);
    axis4 = transFMat * axis4;
    Point4f vertice4(vertice, 1);
    vertice4 = transFMat * vertice4;
    center = base4.toVector3f();
    axis = axis4.toVector3f();
    vertice = vertice4.toVector3f();
}