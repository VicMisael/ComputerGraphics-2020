#include "Ray.hpp"
#include "VectorUtilities.hpp"

Ray::Ray(Point3f origin, Vector3f D)
{
	this->O = origin;
	this->D = VectorUtilities::normalizeCopy(D);
}

Point3f Ray::getPoint(const float t) const
{
	return (O + D * t);
}

Point4f Ray::getOriginInPoint4f()
{
	return Point4f(O.x, O.y, O.z, 1);
}

Vector4f Ray::getDirectionInVector4f()
{
	return Vector4f(D.x, D.y, D.z, 0);
}
