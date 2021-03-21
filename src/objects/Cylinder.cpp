#include "Cylinder.hpp"

Cylinder::Cylinder(Vector3f axis, float height, float radius)
{
	this->Center = Point3f(0, 0, 0);
    this->axis = axis;
    this->axis.normalize();
    this->height = height;
	this->radius = radius;

}

int Cylinder::Intersects(Ray& ray)
{
    Point3f p0 = ray.O; //P0;
    Vector3f d = ray.D; //Vetor direção do raio;

    Vector3f NewCenter = p0 - Center; //Pegar o vetor direção do raio pro centro do cilindro;

    //Multiplica o eixo pelo NewCenter -> Produto escalar;
    axis * VectorUtilities::dotProduct(NewCenter,axis);
    

}

void Cylinder::Translate(float tx, float ty, float tz)
{

}
void Cylinder::RotateX(float angle)
{

}
void Cylinder::RotateY(float angle)
{

}
void Cylinder::RotateZ(float angle)
{

}
void Cylinder::ApplyTransformation()
{

}
