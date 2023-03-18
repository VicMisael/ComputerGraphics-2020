#include "Light.hpp"
#include "VectorUtilities.hpp"
Light::Light(Point3f point, Vector3f Direction, float intensity)
{
    this->intensity = intensity;
    this->Direction = glm::normalize(Direction);
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
void Light::ApplyCamera(const Matrix4x4 m)
{
    using namespace VectorUtilities;
    point = m * point;
    Vector4f dir=Vector4f(Direction,0);
    Direction = glm::normalize(toVector3f(m * dir));
}
Point3f Light::getPosition() { return point; }