#include "Light.hpp"
Light::Light(Point3f point, Vector3f Direction, float intensity)
{
    this->intensity = intensity;
    this->Direction = Direction;
    this->point = point;
}

void Light::SetType(LightType lt)
{
    this->lt = lt;
}

float Light::getIntensity()
{
    return intensity;
}

Point3f Light::getDirection()
{
    return Direction;
}
void Light::ApplyCamera(Matrix4x4 m)
{
    point = m * point;
}
Point3f Light::getPosition() { return point; }