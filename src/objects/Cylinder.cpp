
#include "Cylinder.hpp"
#include <vector>
#include <algorithm>
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



std::tuple<int, float, Vector3f> Cylinder::Intersects(const Ray& ray)
{
		float t_min = INFINITY;
		Point3f p0 = ray.O; //P0;
		Vector3f d = ray.D;; //Vetor direção do raio;
		using namespace VectorUtilities;
		float nx, ny, nz;
		bool basesIsTheClosestIntersected = false;
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
			return NO_INTERSECT;
		}
		float int1 = (-1 * b + sqrtf(delta)) / a;
		float int2 = (-1 * b - sqrtf(delta)) / a;
		Point3f p0r = ray.getPoint(int1);
		Point3f p1r = ray.getPoint(int2);
		float hPo = dotProduct(Base - p0r, axis);
		float hPo1 = dotProduct(Base - p1r, axis);
		int intersecs=0;
		if ((0 <= hPo && hPo <= height)) {
			intersecs++;
			t_min=std::min(int1, t_min);
		}
		if ((0 <= hPo1 && hPo1 <= height)) {
			intersecs++;
			t_min = std::min(int2, t_min);
		}
		if (intersecs < 2) {
			Point3f top_center = Base + axis * height;
			Plane plane_base(axis, Base, this->BaseColor);
			Plane plane_top(axis, top_center, this->BaseColor);
			const auto [intersects_base,t_base,base_normal] = plane_base.Intersects(ray);
			if (intersects_base && fabs(t_base) < t_min) {
				const float t = t_base;
				Point3f intpoint = ray.getPoint(t);
				Vector3f difBaseP = intpoint - Base;

				if (difBaseP.length() <= radius) {
					basesIsTheClosestIntersected = true;
					intersecs++;
					t_min = std::min(fabs(t), t_min);
				}
				nx = base_normal.x;
				ny = base_normal.y;
				nz = base_normal.z;

			}

			const auto [intersects_top, t_top,top_normal] = plane_top.Intersects(ray);
			if (intersects_top && fabs(t_top)<t_min) {
				const float t = t_top;
				Point3f intpoint = ray.getPoint(t);
				Vector3f difBaseP = Base - intpoint;

				if (difBaseP.length() <= radius) {
					basesIsTheClosestIntersected = true;
					intersecs++;
					t_min = std::min(fabs(t), t_min);
				}

				nx = top_normal.x;
				ny = top_normal.y;
				nz = top_normal.z;
			}
	
		}
		if (!basesIsTheClosestIntersected) {
			Vector3f normal=getNormal(ray.getPoint(t_min));
			nx = normal.x;
			ny = normal.y;
			nz = normal.z;
		}
	


		return { intersecs > 0, t_min,Vector3f(nx,ny,nz)};

}

Color Cylinder::getColor()
{
	return c;
}


void Cylinder::ApplyTransformation()
{
	Point3f top = transFMat * (Base + axis * height);
	Base = transFMat * Base;
	Vector3f eixo = (top - Base);
	eixo.normalize();
	axis = eixo;
	computeAABB();
}
void Cylinder::computeAABB() {
	Matrix4x4 matrix;
	matrix.ConcatRotateX(PI / 2);
	Vector3f xAxisProjection = (matrix * Vector4f(axis, 0)).toVector3f();
	matrix.loadIdentity();
	matrix.ConcatRotateZ(PI / 2);
	Vector3f zAxisProjection = (matrix * Vector4f(axis, 0)).toVector3f();
	Point3f topPoint = axis * height;

	std::vector<float> elementsX{
		(xAxisProjection * radius).x,
		(xAxisProjection * (-1.0f * radius)).x,
		(zAxisProjection * radius).x,
		(zAxisProjection * (-1.0f * radius)).x,
		(topPoint + xAxisProjection * radius).x,
		(topPoint + xAxisProjection * (-1.0f * radius)).x,
		(topPoint + zAxisProjection * radius).x,
		(topPoint + zAxisProjection * (-1.0f * radius)).x };
	std::vector<float> elementsY{
		(xAxisProjection * radius).y,
		(xAxisProjection * (-1.0f * radius)).y,
		(zAxisProjection * radius).y,
		(zAxisProjection * (-1.0f * radius)).y,
		(topPoint + xAxisProjection * radius).y,
		(topPoint + xAxisProjection * (-1.0f * radius)).y,
		(topPoint + zAxisProjection * radius).y,
		(topPoint + zAxisProjection * (-1.0f * radius)).y };

	std::vector<float> elementsZ{
		(xAxisProjection * radius).z,
		(xAxisProjection * (-1.0f * radius)).z,
		(zAxisProjection * radius).z,
		(zAxisProjection * (-1.0f * radius)).z,
		(topPoint + xAxisProjection * radius).z,
		(topPoint + xAxisProjection * (-1.0f * radius)).z,
		(topPoint + zAxisProjection * radius).z,
		(topPoint + zAxisProjection * (-1.0f * radius)).z };

	this->maximalPoint = Point3f(
		*std::max_element(elementsX.begin(), elementsX.end()),
		*std::max_element(elementsY.begin(), elementsY.end()),
		*std::max_element(elementsZ.begin(), elementsZ.end())
	);
	this->minimalPoint = Point3f(
		*std::min_element(elementsX.begin(), elementsX.end()),
		*std::min_element(elementsY.begin(), elementsY.end()),
		*std::min_element(elementsZ.begin(), elementsZ.end())
	);

	this->aabb = AABB(this->minimalPoint,this->maximalPoint);
}
Vector3f Cylinder::getNormal(const Point3f p)
{
	using namespace VectorUtilities;
	Vector3f W= p-Base;
	Vector3f N = (W-axis*dotProduct(W,axis));
	N.normalize();
	return N;

}

void Cylinder::ApplyCamera(const Matrix4x4 m)
{
	Point3f top =m*(Base + axis * height);
	Base = m*Base;
	Vector3f eixo = (top - Base);
	eixo.normalize();
	this->axis = eixo;
	computeAABB();
	//
	//axis=m* top-Base;
	//axis.normalize();
}
