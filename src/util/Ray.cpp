#include "Ray.hpp"


Ray::Ray(Point3f point, Vector3f D, float t)
{
	this->O = point;
	this->D = D;
	this->t = t;
	this->D.normalize();
}

Point3f Ray::getPoint(float t)
{
	return (O + D * t);
}

Point4f Ray::getOriginInPoint4f()
{
	return Point4f(O.x,O.y,O.z,1);
}

Vector4f Ray::getDirectionInVector4f()
{
	return Vector4f(D.x,D.y,D.z,0);
}
