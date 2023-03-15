#include "Cone.hpp"
#include <vector>
#include <algorithm>
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

std::tuple<int, float, Vector3f>Cone::Intersects(const Ray& ray)
{
        float t_min = INFINITY;
        int intersections = 0;
        Point3f Po = ray.O;

        const Vector3f d = ray.D;
        const Vector3f n = Vector3f(axis);
        const Vector3f v = (vertice-Po);
    
        using namespace VectorUtilities;
        using namespace std;
    


        const float a = (dotProduct(d, n) * dotProduct(d, n)) - dotProduct(d, d) * cos2Theta;
        const float b = dotProduct(v, d) * cos2Theta - dotProduct(v, n) * dotProduct(d, n);
        const float c = (dotProduct(v, n) * dotProduct(v, n)) - dotProduct(v, v) * cos2Theta;
        const float delta = b * b - (a * c);
        if (delta > 0)
        {
            const float sqrtDelta = sqrtf(delta);
            float t1= (-b + sqrtDelta)/ a;
            float t2 =(-b - sqrtDelta)/ a;
            Point3f p1 = ray.getPoint(t1);
            Point3f p2 = ray.getPoint(t2);
            float dp1 = dotProduct(vertice - p1, n);
            float dp2 = dotProduct(vertice - p2, n);
            if ( (0 <= dp1 && dp1 <= height)) {
               
                intersections++;
                t_min = std::min(t1,t_min);
            }
            if ((0 <= dp2 && dp2 <= height))
            {
                intersections++;
                t_min = std::min(t2, t_min);
            }

        }
    
        return { intersections > 0,t_min,getNormal(ray.getPoint(t_min))};
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
    computeAABB();
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
    computeAABB();
    //std::cout << axis.length()<<std::endl;
    //vertice = mm44*vertice;
}

void Cone::computeAABB()
{
    Matrix4x4 matrix;
    matrix.ConcatRotateX(PI / 2);
    Vector3f xAxisProjection = (matrix * Vector4f(axis, 0)).toVector3f();
    matrix.loadIdentity();
    matrix.ConcatRotateZ(PI / 2);
    Vector3f zAxisProjection = (matrix * Vector4f(axis, 0)).toVector3f();
    Point3f topPoint = axis * height;
    std::vector<float> elementsX{
    (xAxisProjection * radius).x,
    (xAxisProjection * (-1.0f * radius)).x,
    (zAxisProjection * radius).x,
    (zAxisProjection * (-1.0f * radius)).x,
    (topPoint + xAxisProjection * radius).x,
    (topPoint + xAxisProjection * (-1.0f * radius)).x,
    (topPoint + zAxisProjection * radius).x,
    (topPoint + zAxisProjection * (-1.0f * radius)).x };
    std::vector<float> elementsY{
        (xAxisProjection * radius).y,
        (xAxisProjection * (-1.0f * radius)).y,
        (zAxisProjection * radius).y,
        (zAxisProjection * (-1.0f * radius)).y,
        (topPoint + xAxisProjection * radius).y,
        (topPoint + xAxisProjection * (-1.0f * radius)).y,
        (topPoint + zAxisProjection * radius).y,
        (topPoint + zAxisProjection * (-1.0f * radius)).y };

    std::vector<float> elementsZ{
        (xAxisProjection * radius).z,
        (xAxisProjection * (-1.0f * radius)).z,
        (zAxisProjection * radius).z,
        (zAxisProjection * (-1.0f * radius)).z,
        (topPoint + xAxisProjection * radius).z,
        (topPoint + xAxisProjection * (-1.0f * radius)).z,
        (topPoint + zAxisProjection * radius).z,
        (topPoint + zAxisProjection * (-1.0f * radius)).z };

    Point3f maximalPoint = Point3f(
        *std::max_element(elementsX.begin(), elementsX.end()),
        *std::max_element(elementsY.begin(), elementsY.end()),
        *std::max_element(elementsZ.begin(), elementsZ.end())
    );
    Point3f minimalPoint = Point3f(
        *std::min_element(elementsX.begin(), elementsX.end()),
        *std::min_element(elementsY.begin(), elementsY.end()),
        *std::min_element(elementsZ.begin(), elementsZ.end())
    );

    this->aabb = AABB(minimalPoint, maximalPoint);
}
