#ifndef _CYLINDER_
#define _CYLINDER_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "AABB.h"
#include "BaseObject.hpp"

class Cylinder final : public BaseObject
{
private: // center of cylinder 
	Vector3f axis; // cylinder axis 
	Point3f Base;
	float height;
	float radius;
	Color BaseColor;
	Point3f minimalPoint;
	Point3f maximalPoint;
	AABB aabb;

public:
	Cylinder(Vector3f axis, float height, float radius, const Color color) : Cylinder(
		axis, height, radius, color, color)
	{
	};
	Cylinder(Vector3f axis, float height, float radius, Color color, Color BaseColor);
	std::tuple<int, float, Vector3f> Intersects(const Ray& ray);
	Color getColor() override;
	void ApplyTransformation() override;
	void computeAABB();
	Vector3f getNormal(Point3f p) override;
	void ApplyCamera(Matrix4x4 m) override;
};

#endif
