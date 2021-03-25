#include "Cone.hpp"
#include <vector>
#include "Plane.hpp"

Cone::Cone(Point3f vertice, Vector3f axis, float height, float radius, Color c)
{
    this->center = Point3f(0,1,0);
    // Eixo que aponta para o topo do cone.
    this->vertice = vertice;
    this->axis = axis;
    this->height = height;
    this->radius = radius;
    this->c = c;
    this->axis.normalize();

}


int Cone::Intersects(Ray& ray)
{
    float t_min = -INFINITY;
    Point3f p0 = ray.O;
    Vector3f d = ray.D;
    using namespace VectorUtilities;

    // Vector v = V - P0
    Vector3f v = (p0-vertice);
    // cos_theta = adj / sqrt(gˆ2 + rˆ2)
    // usando cos_theta ^ 2
    float cos_sqrd_theta = std::pow(height / std::sqrt(std::pow(height, 2) + std::pow(radius, 2)), 2);
    float a = std::pow(dotProduct(d,axis), 2) - (dotProduct(d,d) * cos_sqrd_theta);
    float b = (dotProduct(d,v) * cos_sqrd_theta) - (dotProduct(v,axis) * cos_sqrd_theta); 
    float c = std::pow(dotProduct(v,axis),2) - (dotProduct(v,axis) * dotProduct(d,axis));
    float delta = std::pow(b,2) - a*c;

    if (delta < 0)
    {
        return 0;
    }

    float int1 = (-1*b + std::sqrt(delta))/a;
    float int2 = (-1*b - std::sqrt(delta))/a;

    Point3f p1 = ray.getPoint(int1);
    Point3f p2 = ray.getPoint(int2);

    float p1_dotproduct = dotProduct(p1-vertice,axis);
    float p2_dotproduct = dotProduct(p2-vertice,axis);

    std::vector<float> intersecs;
    if (int1 >= 0 && (0 <= p1_dotproduct && p1_dotproduct <= height))
        intersecs.push_back(int1);
    if (int2 >= 0 && (0 <= p2_dotproduct && p2_dotproduct <= height))
        intersecs.push_back(int2);
    
    // Uma interseção com a face do cone
    // A outra pode acontecer com a base

    if ((int)intersecs.size() == 1)
    {
        Plane plane_base = Plane(axis,center,Color(0,0,0));
        float t_base;
        int base_intersection = plane_base.Intersects(ray);
        if (base_intersection)
        {
            Point3f p_base = ray.getPoint(t_base);
            Vector3f cbase = center - p_base;
            if(t_base >= 0 && cbase.length() < radius)
                intersecs.push_back(t_base);
        }
    }

    int int_candidates = (int) intersecs.size();

    t_min = int_candidates != 0 ? intersecs[0] : t_min;
    for (int i = 1; i < int_candidates; i++)
        if(intersecs[i] < t_min)
            t_min = intersecs[i];
    return int_candidates >= 1;
    
}

void Cone::ApplyTransformation()
{
    Point4f base4(center,1);
    base4 = transFMat * base4;
    Vector4f axis4(axis,0);
    axis4 = transFMat*axis4;
    Point4f vertice4(vertice,0);
    vertice4 = transFMat * vertice4;
    center = base4.toVector3f();
    axis = axis4.toVector3f();    
    vertice = vertice4.toVector3f();
}