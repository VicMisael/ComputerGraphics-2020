#ifndef _VECTOR3F_
#define _VECTOR3F_
#ifdef _USESIMDINTRINSICS
#include <xmmintrin.h>
#endif
#include <math.h>
#include "definitions.hpp"

//Can be used to represent both vectors, and points
class Vector3f
{

public:
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(float vec[3]);
    #ifdef _USESIMDINTRINSICS
    Vector3f(__m128 xyz);
    #endif

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
        #ifdef _USESIMDINTRINSICS
        __m128 xyz;
        #endif
        float vec[3];
        struct
        {
            float x, y, z;
        };
    };
};
#endif