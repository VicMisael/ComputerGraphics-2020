#include "Plane.hpp"



Plane::Plane(Vector3f _u, Point3f _kp, Color color)
{
	n = _u;
	pplane = _kp;
	n.normalize();
	c = color;
}

int Plane::Intersects(Ray& ray)
{
	t_min = INFINITY;
	using namespace VectorUtilities;
	Vector3f p0 = ray.O;
	Vector3f Dir = ray.D;
	float dn = dotProduct(Dir, n);
	if (dn == 0) {
		return 0;
	}
	float intersection = dotProduct(pplane-p0, n) / dn;
	if (intersection < 0){
		return 0;
	}
	t_min = intersection;
	//std::cout << "plane intPoint x: " << ray.getPoint(t_min).x << " y: " << ray.getPoint(t_min).y << " z: " << ray.getPoint(t_min).z << std::endl;
	//std::cout<<"X:"<<IP.x<<"Y:"<<IP.y<<"Z:"<<IP.z<<std::endl;
	return 1;

}


void Plane::ApplyTransformation()
{
	Vector4f NormalVector=Vector4f(n, 0);
	NormalVector=transFMat* NormalVector;
	Point4f Point = Vector4f(pplane, 1);
	Point=transFMat* Point;
	n = NormalVector.toVector3f();
	pplane = Point.toVector3f();
}

Vector3f Plane::getNormal(const Point3f p)
{
	return n;
}
