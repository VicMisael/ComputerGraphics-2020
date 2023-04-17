#ifndef _AABB_
#define _AABB_
#include "BaseObject.hpp"
#include "../util/Vector3f.hpp"

class AABB
{
private:
	Vector3f min;
	Vector3f max;

public:
	AABB() : AABB(Vector3f(0, 0, 0), Vector3f(0, 0, 0))
	{
	};

	AABB(const Vector3f& minV, const Vector3f& maxV)
	{
		this->min = Vector3f(minV.x, minV.y, minV.z);
		this->max = Vector3f(maxV.x, maxV.y, maxV.z);
	};

	int intersects(const Ray& ray)
	{
		const Vector3f& dir = ray.D;
		const Vector3f invdir(1 / dir.x, 1 / dir.y, 1 / dir.z);
		float tmin = (min.x - ray.O.x) / ray.D.x;
		float tmax = (max.x - ray.O.x) / ray.D.x;

		if (tmin > tmax) std::swap(tmin, tmax);

		float tymin = (min.y - ray.O.y) / ray.D.y;
		float tymax = (max.y - ray.O.y) / ray.D.y;

		if (tymin > tymax) std::swap(tymin, tymax);

		if ((tmin > tymax) || (tymin > tmax))
			return false;

		if (tymin > tmin)
			tmin = tymin;

		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (min.z - ray.O.z) / ray.D.z;
		float tzmax = (max.z - ray.O.z) / ray.D.z;

		if (tzmin > tzmax) std::swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;

		if (tzmin > tmin)
			tmin = tzmin;

		if (tzmax < tmax)
			tmax = tzmax;

		return true;
	};
};
#endif // !_AABB_
