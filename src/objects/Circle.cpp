#include "Circle.hpp"
Circle::Circle(float radius, Color c)
{
	this->Center = Point3f(0, 0, 0);
	this->radius = radius;
	this->c = c;
}
int Circle::Intersects(Ray &ray)
{
	using namespace VectorUtilities;
	t_min = INFINITY;
	float a = 1;//dotProduct(ray.D, ray.D);
	float b = dotProduct(ray.O - Center, ray.D);
	float c = dotProduct(ray.O - Center, ray.O - Center) - radius * radius;
	float delta = (b * b) - (a * c);
	if (delta < 0)
	{
		return 0;
	}if (delta == 0) {
		t_min=-b / a;
		return 1;
	}
	float int1 = (-b + sqrt(delta)) / a;
	float int2 = (-b - sqrt(delta)) / a;
	//get the smallest
	t_min = (int1 > int2) ? int2 : int1;

	return 1;
}

Vector3f Circle::getNormal(const Point3f p){
	Vector3f pMc= p-Center;
	pMc.normalize();
	return pMc;
}

void Circle::ApplyCamera(const Matrix4x4 m)
{
	Vector4f Center4f(Center, 1);
	Center4f=m* Center4f;
	Center = Center4f.toVector3f();
	//std::cout << "Ball vector" << std::endl;

}

void Circle::ApplyTransformation()
{
	Vector4f Center4f(Center, 1);
	Center4f = transFMat * Center4f;
	Center= Center4f.toVector3f();

}
