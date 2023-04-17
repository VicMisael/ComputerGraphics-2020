#include "Circle.hpp"
#include <glm/glm.hpp>

Circle::Circle(float radius, Color c)
{
	this->Center = Point3f(0, 0, 0);
	this->radius = radius;
	this->c = c;
}

std::tuple<int, float, Vector3f> Circle::Intersects(const Ray& ray)
{
	if (aabb.intersects(ray))
	{
		using namespace VectorUtilities;
		float t_min = INFINITY;
		float a = 1; //dotProduct(ray.D, ray.D);
		const float b = dotProduct(ray.O - Center, ray.D);
		const float c = dotProduct(ray.O - Center, ray.O - Center) - radius * radius;
		const float delta = (b * b) - (a * c);
		if (delta < 0)
		{
			return NO_INTERSECT;
		}
		if (delta == 0)
		{
			t_min = -b / a;
			return {1, t_min, getNormal(ray.getPoint(t_min))};
		}
		const float int1 = (-b + sqrt(delta)) / a;
		const float int2 = (-b - sqrt(delta)) / a;
		//get the smallest
		t_min = std::min(int1, int2);
		return {1, t_min, getNormal(ray.getPoint(t_min))};
	}
	return NO_INTERSECT;
}

Vector3f Circle::getNormal(const Point3f p)
{
	Vector3f pMc = normalize(p - Center);
	return pMc;
}

void Circle::ApplyCamera(const Matrix4x4 m)
{
	using namespace VectorUtilities;
	Vector4f Center4f(Center, 1);
	Center4f = m * Center4f;
	Center = Vector3f(Center4f);
	//std::cout << "Ball vector" << std::endl;
	computeAABB();
}

void Circle::computeAABB()
{
	float cx = Center.x;
	float cy = Center.y;
	float cz = Center.z;
	this->aabb = AABB(Point3f(
		                  std::fmax(cx + radius, cx - radius),
		                  std::fmax(cy + radius, cy - radius),
		                  std::fmax(cz + radius, cz - radius)
	                  )
	                  , Point3f(
		                  std::fmin(cx + radius, cx - radius),
		                  std::fmin(cy + radius, cy - radius),
		                  std::fmin(cz + radius, cz - radius)
	                  ));
}

void Circle::ApplyTransformation()
{
	Vector4f Center4f(Center, 1);
	Center4f = transFMat * Center4f;
	Center = Center4f.xyz();
	computeAABB();
}
