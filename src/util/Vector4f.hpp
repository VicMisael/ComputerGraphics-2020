#ifndef _VECTOR4F_
#define _VECTOR4F_
#ifndef _USESIMDINTRINSICS
#include <xmmintrin.h>
#endif
#include "Vector3f.hpp"
#include <math.h>
#include "definitions.hpp"

class Vector4f
{
public:
    Vector4f(float x, float y, float z, float w);
    Vector4f(Vector3f vec3);
    Vector4f(float vec[4]);
#ifdef _USESIMDINTRINSICS
    Vector4f(__m128 xyzw);
#endif
    Vector4f();
    Vector4f operator*(const float &a) const
    {
        return Vector4f(a * x, a * y, a * z, a * w);
    }
    Vector4f operator+(const Vector4f &v) const
    {
        return Vector4f(v.x + x, v.y + y, v.z + z, v.w + w);
    }
    Vector4f operator-(const Vector4f &v) const
    {
        return Vector4f(v.x - x, v.y - y, v.z - z, v.w - w);
    }
    Vector3f operator=(const Vector4f &v) const{
        return Vector3f(v.x/v.w,v.y/v.w,v.z/v.w);
    }

    float length();
    void normalize();
    union
    {
#ifdef _USESIMDINTRINSICS
        __m128 xyzw;
#endif
        float vec[4];
        struct
        {
            float x, y, z, w;
        };
    };
};

using Point4f = Vector4f;
#endif