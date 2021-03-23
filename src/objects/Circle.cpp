#include "Circle.hpp"
Circle::Circle(float radius, Color c)
{
	this->Center = Point3f(0, 0, 0);
	this->radius = radius;
	this->c = c;
}
int Circle::Intersects(Ray &ray)
{
	float a = VectorUtilities::dotProduct(ray.D, ray.D);
	float b =  VectorUtilities::dotProduct(ray.O - Center, ray.D);
	float c = VectorUtilities::dotProduct(ray.O - Center, ray.O - Center) - (double)radius * radius;
	float delta = (b * b) - (a * c);
	if (delta < 0)
	{
		return 0;
	}
	return 1;
}



void Circle::ApplyTransformation()
{
	Center = transFMat * Center;
}
