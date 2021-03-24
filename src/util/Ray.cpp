#include "Ray.hpp"

Ray::Ray(Point3f point, Point3f eye) {
	this->O = point;
	this->t = 1;
	this->D = Point3f(0, 0, 0);
	this->D = eye-point;
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
