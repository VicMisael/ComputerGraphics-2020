#include "VectorUtilities.hpp"
#include <iostream>
Vector3f inline VectorUtilities::crossProduct(const Vector3f &a, const Vector3f &b)
{

    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
float VectorUtilities::dotProduct(const Vector3f &a, const Vector3f &b)
{
#ifdef _USESIMDINTRINSICS
    float scalar = 0;
    __m128 val= _mm_dp_ps(a.xyz, b.xyz, 0b01111001);
    scalar=_mm_cvtss_f32(val);
#else
    float scalar = 0;
    for (int i = 0; i < 3; i++)
    {
        scalar += a.vec[i] * b.vec[i];
    }
#endif
    return scalar;
}
Vector3f VectorUtilities::normalizeCopy(const Vector3f &v)
{
#ifdef _USESIMDINTRINSICS
    Vector3f vec(v.xyz);
#else
    Vector3f vec(v.x, v.y, v.z);
#endif

    vec.normalize();
    return vec;
}
float VectorUtilities::Length(const Vector3f &a, const Vector3f &b)
{
    return sqrt(VectorUtilities::dotProduct(a, b));
}
//Vector 4f

float VectorUtilities::dotProduct(const Vector4f &a, const Vector4f &b)
{

#ifdef _USESIMDINTRINSICS
    float scalar = 0;
    __m128 val= _mm_dp_ps(a.xyzw, b.xyzw, 0b11111001);
    scalar=_mm_cvtss_f32(val);
#else
    float scalar = 0;
    for (int i = 0; i < 4; i++)
    {
        scalar += a.vec[i] * b.vec[i];
    }
#endif
    return scalar;
}
Vector4f VectorUtilities::normalizeCopy(const Vector4f &v)
{
#ifdef _USESIMDINTRINSICS
    Vector4f vec(v.xyzw);
#else
    Vector4f vec(v.x, v.y, v.z, v.w);
#endif

    vec.normalize();
    return vec;
}

float VectorUtilities::Length(const Vector4f &a, const Vector4f &b)
{
    return sqrt(VectorUtilities::dotProduct(a, b));
}