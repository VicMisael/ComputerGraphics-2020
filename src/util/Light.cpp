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
    return intensity > 1 ? 1 : intensity;
}

Point3f Light::getDirection()
{
    return Direction;
}
Point3f Light::getPosition() { return point; }