#ifndef _LIGHT_
#include "Vector3f.hpp"
enum LightType
{
    ambient,
    point,
    directional

};

class Light
{
    Point3f point;
    Vector3f Direction;
    float intensity;

public:
    LightType lt = ambient;
    Light(const Point3f point, const Vector3f Direction, float intensity);
    void SetType(LightType lt);
    float getIntensity();
    Point3f getPosition();
    Vector3f getDirection();
};

#endif