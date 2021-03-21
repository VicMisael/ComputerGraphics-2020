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
	float b = 2 * VectorUtilities::dotProduct(ray.O - Center, ray.D);
	float c = VectorUtilities::dotProduct(ray.O - Center, ray.O - Center) - (double)radius * radius;
	float delta = (b * b) - (4 * a * c);
	if (delta < 0)
	{
		return 0;
	}
	else if (delta == 0)
	{
		return 1;
	}
	return 2;
}

void Circle::Translate(float x, float y, float z)
{
	transFMat.ConcatTranslate(x, y, z);
}

void Circle::ApplyTransformation()
{
	Center = transFMat * Center;
}

void Circle::RotateX(float angle)
{
	transFMat.ConcatRotateX(angle);
}

void Circle::RotateY(float angle)
{
	transFMat.ConcatRotateY(angle);
}

void Circle::RotateZ(float angle)
{
	transFMat.ConcatRotateZ(angle);
}
