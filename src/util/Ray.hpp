#ifndef _RAY_
#define _RAY_
#include "Vector3f.hpp"
#include "Vector4f.hpp"

class Ray
{
public:
	Point3f O;
	Vector3f D;
	Ray(Point3f origin, Vector3f D);
	Point3f getPoint(float t) const;
	Vector4f getOriginInPoint4f();
	Vector4f getDirectionInVector4f();
};

#endif
