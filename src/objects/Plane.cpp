#include "Plane.hpp"



Plane::Plane(Vector3f _u, Point3f _kp, Color color)
{
	u = _u;
	kp = _kp;
	c = color;
}

int Plane::Intersects(Ray& ray)
{	
	t_min = -INFINITY;
	using namespace VectorUtilities;
	Vector3f p0 = ray.O;
	Vector3f Dir = ray.D;
	float dn=dotProduct(Dir, u);
	if (dn == 0) {
		return 0;
	}
	float intersection =dotProduct(kp - p0, u)/dn;
	t_min = intersection;
	return 1;

}


void Plane::ApplyTransformation()
{
}
