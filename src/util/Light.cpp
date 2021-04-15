#include "Light.hpp"
Light::Light(Point3f point, Vector3f Direction, float intensity)
{
    this->intensity = intensity;
    this->Direction = Direction;
    this->point = point;
    Direction.normalize();
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
void Light::ApplyCamera(const Matrix4x4 m)
{
    point = m * point;
    Vector4f dir=Vector4f(Direction,0);
    Direction=(m*dir).toVector3f();
    Direction.normalize();
}
Point3f Light::getPosition() { return point; }