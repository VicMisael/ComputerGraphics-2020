#ifndef _VECTOR3F_
#define _VECTOR3F_
#include <xmmintrin.h>
#include <math.h>
class Vector3f
{

public:
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(float vec[3]);
    Vector3f(__m128 xyz);

    Vector3f operator*(const float &a) const
    {
        return Vector3f(a * x, a * y, a * z);
    }
    Vector3f operator+(const Vector3f &v) const
    {
        return Vector3f(v.x + x, v.y + y, v.z + z);
    }
    Vector3f operator-(const Vector3f &v) const
    {
        return Vector3f(v.x - x, v.y - y, v.z - z);
    }
    float length();
    void normalize();
    union
    {
        __m128 xyz;
        float vec[3];
        struct
        {
            float x, y, z;
        };
    };
};
#endif