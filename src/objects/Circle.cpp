#include "Circle.hpp"
Circle::Circle(float radius, Color c)
{
	this->Center = Point3f(0, 0, 0);
	this->radius = radius;
	this->c = c;
}
int Circle::Intersects(Ray &ray)
{
	t_min = -INFINITY;
	float a = VectorUtilities::dotProduct(ray.D, ray.D);
	float b =  VectorUtilities::dotProduct(ray.O - Center, ray.D);
	float c = VectorUtilities::dotProduct(ray.O - Center, ray.O - Center) - (double)radius * radius;
	float delta = (b * b) - (a * c);
	if (delta < 0)
	{
		return 0;
	}if (delta == 0) {
		t_min=-b / a;
	}
	float int1 = (-1 * b + sqrtf(delta)) / a;
	float int2 = (-1 * b - sqrtf(delta)) / a;
	float t_min = (int1 > int2) ? int2 : int1;
	return 1;
}



void Circle::ApplyTransformation()
{
	Center = transFMat * Center;
}
