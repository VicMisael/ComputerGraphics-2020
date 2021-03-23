#include "Vector4f.hpp"


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
Vector4f::Vector4f(Vector3f vec, int _w)
{
    x=vec.x;
    y=vec.y;
    z=vec.z;
    w = _w;
}
Vector3f Vector4f::toVector3f() {
    if (w > 0 || w==1) {
        return Point3f(x / w, y / w, z / w);
    }
    return Vector3f(x, y, z);

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

float Vector4f::length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}
