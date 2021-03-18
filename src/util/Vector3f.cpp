#include "Vector3f.hpp"
Vector3f::Vector3f()
{
    Vector3f(0, 0, 0);
}
Vector3f::Vector3f(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}
Vector3f::Vector3f(float _vec[3])
{
    for (int i = 0; i < 3; i++)
    {
        vec[i] = _vec[i];
    }
}
#ifdef _USESIMDINTRINSICS
Vector3f::Vector3f(__m128 _xyz)
{
    xyz = _xyz;
}
#endif
void Vector3f::normalize()
{
    float length = this->length();
    if (length != 0)
    { //Using Inntrinsics for SIMD
#ifdef _USESIMDINTRINSICS
        const __m128 scalar = _mm_set1_ps(length);
        xyz = _mm_div_ps(xyz, scalar);
#else
        x *= 1 / length;
        y *= 1 / length;
        z *= 1 / length;
#endif
    }
}
float Vector3f::length()
{
    return sqrt(x * x + y * y + z * z);
}