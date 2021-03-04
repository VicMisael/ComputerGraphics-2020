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