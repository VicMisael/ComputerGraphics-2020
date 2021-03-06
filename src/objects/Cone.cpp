#include "Cone.hpp"
#include <vector>
#include "Plane.hpp"

Cone::Cone( Vector3f axis, float height, float radius, Color c)
{
    this->center = Point3f(0, 0, 0);
    // Eixo que aponta para o topo do cone.
    axis.normalize();
    this->axis = axis;
    this->vertice = center+(axis*height);
    this->height = height;
    this->radius = radius;
    this->c = c;
    this->axis.normalize();
    float hipothenuse = sqrtf((radius * radius) + (height * height));
    this->cosTheta = height / hipothenuse;
    this->cos2Theta= powf(cosTheta, 2);
}

int Cone::Intersects(Ray& ray)
{
    t_min = INFINITY;
    Point3f Po = ray.O;

    Vector3f d = ray.D;
    Vector3f n = Vector3f(axis);
    Vector3f v = (vertice-Po);
    
    using namespace VectorUtilities;
    using namespace std;
    


    float a = (dotProduct(d, n) * dotProduct(d, n)) - dotProduct(d, d) * cos2Theta;
    float b = dotProduct(v, d) * cos2Theta - dotProduct(v, n) * dotProduct(d, n);
    float c = (dotProduct(v, n) * dotProduct(v, n)) - dotProduct(v, v) * cos2Theta;
    float delta = b * b - (a * c);
    vector<float> intersections;
    if (delta > 0)
    {
        float t1= (-b + sqrtf(delta))/ a;
        float t2 =(-b - sqrtf(delta))/ a;
        Point3f p1 = ray.getPoint(t1);
        Point3f p2 = ray.getPoint(t2);
        float dp1 = dotProduct(vertice - p1, n);
        float dp2 = dotProduct(vertice - p2, n);
        if ( (0 <= dp1 && dp1 <= height)) {
            intersections.push_back(t1);
        }
        if ((0 <= dp2 && dp2 <= height))
        {
            intersections.push_back(t2);
        }

    }
     

    if (intersections.size() < 2 ) {
        //Plane base(center, n, this->c);
        //if (base.Intersects(ray)) {
        //   float t=base.getTmin();
        //   if (t > 0) {
        //       intersections.push_back(t);
        //   }
        //   }
    }
    for(float t:intersections){
        if (t < t_min)
            t_min = t;
    }
    return intersections.size() > 0;
}

void Cone::ApplyTransformation()
{
    Point4f base4(center, 1);
    base4 = transFMat * base4;
    Vector4f axis4(axis, 0);
    //axis4 = transFMat * axis4;
    Point4f vertice4(vertice, 1);
    vertice4 = transFMat * vertice4;
    center = base4.toVector3f();
    //axis = axis4.toVector3f();
    vertice = vertice4.toVector3f();
    axis = vertice - center;
    float hipothenuse = sqrtf((radius * radius) + (height * height));
    this->cosTheta = height / hipothenuse;
}

Vector3f Cone::getNormal(const Point3f p)
{
    Vector3f v = vertice - p;
    v.normalize();
    Vector3f Normal = axis - v*cosTheta ;
    Normal.normalize();
    return Normal;
}

void Cone::ApplyCamera(const Matrix4x4 mm44)
{
    center = mm44 * center;
    vertice = mm44 * vertice;
    Vector3f eixo=vertice - center;
    eixo.normalize();
    this->axis = eixo;
    //std::cout << axis.length()<<std::endl;
    //vertice = mm44*vertice;
}
