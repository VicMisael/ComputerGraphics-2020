#include "Ray.hpp"

Ray::Ray(Point3f point, Point3f eye) {
	this->O = point;
	this->t = 1;
	this->D = Point3f(0, 0, 0);
	this->D = point - eye;
	this->D.normalize();
}