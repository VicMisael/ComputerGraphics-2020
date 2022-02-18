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
    const float Epsilon = 10e-10;
    if (fabs(w)<=Epsilon) {
        return Point3f(x , y , z);
    }
    return Vector3f(x/w , y/w, z/w);

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

        x *= 1 / length;
        y *= 1 / length;
        z *= 1 / length;
        w *= 1 / length;

    }
}

float Vector4f::length()
{
    return sqrtf(x * x + y * y + z * z + w * w);
}
