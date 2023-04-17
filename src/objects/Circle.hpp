#ifndef _CIRCLE_
#define _CIRCLE_
#include <cmath>
#include <tuple>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "AABB.h"
#include "BaseObject.hpp"

class Circle final : public BaseObject
{
private:
	AABB aabb;
	float radius;
	Point3f Center;

public:
	Circle(float radius, Color c);
	std::tuple<int, float, Vector3f> Intersects(const Ray& ray);
	void ApplyTransformation() override;
	Vector3f getNormal(Point3f p) override;
	void ApplyCamera(Matrix4x4 m) override;
	void computeAABB();
};
#endif
