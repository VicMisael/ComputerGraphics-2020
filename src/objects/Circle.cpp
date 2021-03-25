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
	t_min = -INFINITY;
	float a = dotProduct(ray.D, ray.D);
	float b =  dotProduct(ray.O - Center, ray.D);
	float c = dotProduct(ray.O - Center, ray.O - Center) - radius * radius;
	float delta = (b * b) - (a * c);
	if (delta < 0)
	{
		return 0;
	}if (delta == 0) {
		t_min=-b / a;
	}
	float int1 = (-b + sqrtf(delta)) / a;
	float int2 = (-b - sqrtf(delta)) / a;
	float t_min = (int1 > int2) ? int2 : int1;
	return 1;
}



void Circle::ApplyTransformation()
{
	Center = transFMat * Center;
}
