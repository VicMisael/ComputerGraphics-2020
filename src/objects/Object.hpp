
#include "../util/Matrix4x4.hpp"
#include "../util/Ray.hpp"
#include "../util/Color.hpp"
class Object
{
public:
    Matrix4x4 m44;
    Color c;
    virtual Color Intersects(Ray &ray);
    virtual void Translate(float tx, float ty, float tz);
};