#include "Vector4f.hpp"

Vector4f::Vector4f()
{
    //creates a point
    Vector4f(1, 0, 0, 1);
}
Vector4f::Vector4f(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}
Vector4f::Vector4f(float _vec[4])
{
    for (int i = 0; i < 4; i++)
    {
        vec[i] = _vec[i];
    }
}
Vector4f::Vector4f(Vector3f vec)
{
#ifdef _USESIMDINTRINSICS
    xyzw = vec.xyz;
#else
    x=vec.x;
    y=vec.y;
    z=vec.z;
#endif
    w = 1;
}
#ifdef _USESIMDINTRINSICS
Vector4f::Vector4f(__m128 _xyzw)
{
    xyzw = _xyzw;
}
#endif
void Vector4f::normalize()
{
    float length = this->length();
    if (length != 0)
    { //Using Inntrinsics for SIMD
#ifdef _USESIMDINTRINSICS
        const __m128 scalar = _mm_set1_ps(length);
        xyzw = _mm_div_ps(xyzw, scalar);
#else
        x *= 1 / length;
        y *= 1 / length;
        z *= 1 / length;
        w *= 1 / length;
#endif
    }
}

Vector3f Vector4f::toVector3f()
{
    return Vector3f(x, y, z);
}
float Vector4f::length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}
