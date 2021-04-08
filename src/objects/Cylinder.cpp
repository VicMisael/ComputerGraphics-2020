
#include "Cylinder.hpp"
#include <vector>
#include "Plane.hpp"

Cylinder::Cylinder(Vector3f axis, float height, float radius, Color c, Color basecolor)
{
	this->Base = Point3f(0, 0, 0);
	this->axis = axis; //eixo que "aponta" pro topo do cilindro
	this->axis.normalize();
	this->height = height;
	this->radius = radius;
	this->BaseColor = basecolor;
	this->c = c;
}

int Cylinder::Intersects(Ray& ray)
{
	t_min = -INFINITY;
	baseIntersected = false;
	Point3f p0 = ray.O; //P0;
	Vector3f d = ray.D;; //Vetor direção do raio;
	using namespace VectorUtilities;
	//Vectors
	Vector3f pMBase = (p0 - Base);
	Vector3f v = pMBase - axis * (dotProduct(pMBase, axis));
	Vector3f w = d - axis * (dotProduct(d, axis));
	float a = dotProduct(w, w);
	float b = dotProduct(v, w);
	float c = dotProduct(v, v) - radius * radius;
	float delta = b * b - (a * c);
	if (delta < 0)
	{
		return 0;
	}
	float int1 = (-1 * b + sqrtf(delta)) / a;
	float int2 = (-1 * b - sqrtf(delta)) / a;
	Point3f p0r = ray.getPoint(int1);
	Point3f p1r = ray.getPoint(int2);
	float hPo = dotProduct(Base - p0r, axis);
	float hPo1 = dotProduct(Base - p1r, axis);
	std::vector<float> intersecs;
	if ((0 <= hPo && hPo <= height)) {
		intersecs.push_back(int1);
	}
	if ((0 <= hPo1 && hPo1 <= height)) {
		intersecs.push_back(int2);
	}
	if (intersecs.size() < 2) {
		Point3f top_center = Base + axis * height;
		Plane plane_base(axis, Base, this->BaseColor);
		Plane plane_top(axis, top_center, this->BaseColor);
		if (plane_base.Intersects(ray)) {
			float t = plane_base.getTmin();
			Point3f intpoint = ray.getPoint(t);
			Vector3f difBaseP = intpoint-Base;
		
			if (difBaseP.length() <= radius) {
				baseIntersected = true;
				intersecs.push_back(fabs(t));
			}


		}
		if (plane_top.Intersects(ray)) {
			float t = plane_top.getTmin();
			Point3f intpoint = ray.getPoint(t);
			Vector3f difBaseP = Base - intpoint;

			if (difBaseP.length() <= radius) {
				baseIntersected = true;
				intersecs.push_back(fabs(t));
			}

		}
	}
	t_min = INFINITY;
	for (float f : intersecs) {
		if (f < t_min) {
			t_min = f;
		}
	}
	return intersecs.size() > 0;
}

Color Cylinder::getColor()
{
	if (baseIntersected) {
		return BaseColor;
	}
	return c;
}


void Cylinder::ApplyTransformation()
{
	Point4f base4(Base, 1);
	base4 = transFMat * base4;
	Vector4f axis4(axis, 0);
	axis4 = transFMat * axis4;
	Base = base4.toVector3f();
	axis = axis4.toVector3f();

}

Vector3f Cylinder::getNormal(const Point3f p)
{
	using namespace VectorUtilities;
	Vector3f W= p-Base;
	Vector3f N = W-axis*dotProduct(W,axis);
	N.normalize();
	return N;

}

void Cylinder::ApplyCamera(const Matrix4x4 m)
{
	Base = m * Base;
}
