#include "Cone.hpp"
#include <vector>
#include "Plane.hpp"

Cone::Cone( Vector3f axis, float height, float radius, Color c)
{
    this->center = Point3f(0, 0, 3);
    // Eixo que aponta para o topo do cone.
    axis.normalize();
    this->axis = axis;
    this->vertice = center+axis*height;
    this->height = height;
    this->radius = radius;
    this->c = c;
    this->axis.normalize();
}

int Cone::Intersects(Ray& ray)
{
    float t_min = INFINITY;
    Point3f Po = ray.O;

    Vector3f d = ray.D;
    Vector3f n = Vector3f(axis);
    Vector3f v = (Po - vertice);
   

    float cosTheta = height / (sqrtf(height * height + radius * radius));
    using namespace VectorUtilities;
    using namespace std;
    float a = dotProduct(d, n) * dotProduct(d, n) - dotProduct(d, d) * (cosTheta * cosTheta);
    float b = dotProduct(v, d) * cosTheta * cosTheta - dotProduct(v, n) * dotProduct(d, n);
    float c = dotProduct(v, n) * dotProduct(v, n) - dotProduct(v, v) * (cosTheta * cosTheta);
    float delta = b * b - (a * c);
    if (delta < 0)
    {
        return 0;
    }
    float t1 = -b - sqrt(delta) / a;
    float t2 = -b + sqrt(delta) / a;
    Point3f p1 = ray.getPoint(t1);
    Point3f p2 = ray.getPoint(t2);
    float dp1 = dotProduct(vertice - p1, n);
    float dp2 = dotProduct(vertice - p2, n);
    vector<float> intersections;
    if (t1 >= 0 && (0 <= dp1 && dp1 <= height)) {
        intersections.push_back(t1);
    }
    if (t2 >= 0 && (0 <= dp2 && dp2 <= height))
    {   
        intersections.push_back(t2);
    }
    if (intersections.size() == 1) {
        Plane base(center, n, this->c);
        if (base.Intersects(ray)) {
           float t=base.getTmin();
           intersections.push_back(t);
        }
    }
    for(float t:intersections){
        if (t < t_min)
            t=t_min;
    }
    return intersections.size() > 0;
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