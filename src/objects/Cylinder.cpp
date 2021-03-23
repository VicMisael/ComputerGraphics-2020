#include "Cylinder.hpp"

Cylinder::Cylinder(Vector3f axis, float height, float radius, Color c)
{
    this->Base = Point3f(0,0,0);
    this->axis = axis; //eixo que "aponta" pro topo do cone
    this->axis.normalize();
    this->height = height;
    this->radius = radius;
    this->c = c;
}

int Cylinder::Intersects(Ray& ray)
{
    Point3f p0 = ray.O; //P0;
    Vector3f d = ray.D;; //Vetor direção do raio;

    //Vectors
    Vector3f pMBase = (Base - p0);
    Vector3f v = pMBase - axis * (VectorUtilities::dotProduct(pMBase, axis));
    Vector3f w = d - axis * (VectorUtilities::dotProduct(d, axis));
    float a = VectorUtilities::dotProduct(w, w);
    float b = VectorUtilities::dotProduct(v, w);
    float c = VectorUtilities::dotProduct(v, v) - radius * radius;
    float delta = b * b - (a * c);
    float t1, t2;
    if (delta < 0)
    {
        return 0;
    }

    return 1;
}


void Cylinder::ApplyTransformation()
{
    Point4f base4(Base,1);
    base4=transFMat* base4;
    Vector4f axis4(axis,0);
    axis4 =  transFMat*axis4;
    Base=base4.toVector3f();
    axis = axis4.toVector3f();

}
