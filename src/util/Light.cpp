#include "Light.hpp"
#include "VectorUtilities.hpp"

Light::Light(Point3f point, Vector3f Direction, float intensity)
{
	this->intensity = intensity;
	this->Direction = normalize(Direction);
	this->point = point;
}

void Light::SetType(LightType lt)
{
	this->lt = lt;
}

float Light::getIntensity() const
{
	return intensity;
}

Point3f Light::getDirection() const
{
	return Direction;
}

void Light::ApplyCamera(const Matrix4x4 m)
{
	using namespace VectorUtilities;
	point = m * point;
	auto dir = Vector4f(Direction, 0);
	Direction = normalize(toVector3f(m * dir));
}

Point3f Light::getPosition() const { return point; }
