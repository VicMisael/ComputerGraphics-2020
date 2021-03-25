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
	Point3f IP=ray.getPoint(t_min);
	//std::cout<<"X:"<<IP.x<<"Y:"<<IP.y<<"Z:"<<IP.z<<std::endl;
	return 1;

}


void Plane::ApplyTransformation()
{
	Vector4f NormalVector=Vector4f(u, 0);
	NormalVector=transFMat* NormalVector;
	Point4f Point = Vector4f(kp, 1);
	Point=transFMat* Point;
	u = NormalVector.toVector3f();
	kp = Point.toVector3f();
}