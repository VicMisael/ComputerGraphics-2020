#include "Plane.hpp"



Plane::Plane(Vector3f _u, Point3f _kp, Color color)
{
	n = _u;
	pplane = _kp;
	c = color;
}

std::tuple<int, float,Vector3f> Plane::Intersects(const Ray& ray)
{
	float t_min = INFINITY;
	using namespace VectorUtilities;
	Vector3f p0 = ray.O;
	Vector3f Dir = ray.D;
	const float dn = dotProduct(Dir, n);
	if (abs(dn) < 0.001) {
		return NO_INTERSECT;
	}
	const float intersection = dotProduct(pplane-p0, n) / dn;
	if (intersection < 0){
		return NO_INTERSECT;
	}

	return {1,intersection,this->getNormal(ray.getPoint(t_min))};

}


void Plane::ApplyTransformation()
{
	Vector4f NormalVector=Vector4f(n, 0);
	NormalVector=transFMat* NormalVector;
	Point4f Point = Vector4f(pplane, 1);
	Point=transFMat* Point;
	n = VectorUtilities::toVector3f(NormalVector);
	pplane = VectorUtilities::toVector3f(Point);
}

Vector3f Plane::getNormal(const Point3f p)
{
	return n;
}

void Plane::ApplyCamera(const Matrix4x4 m)
{
	pplane = m * pplane;
	Vector4f normal = Vector4f(n,0);
	normal=m* normal;
	n = VectorUtilities::toVector3f(normal);
	//n.normalize();
}
