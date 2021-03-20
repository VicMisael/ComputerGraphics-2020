#include "VectorUtilities.hpp"
#include <iostream>
Vector3f VectorUtilities::crossProduct(const Vector3f &a, const Vector3f &b)
{

    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double VectorUtilities::dotProduct(const Vector3f &a, const Vector3f &b)
{
    double scalar = 0;
    for (int i = 0; i < 3; i++)
    {
        scalar += (double)a.vec[i] * (double)b.vec[i];
    }

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
double VectorUtilities::Length(const Vector3f &a, const Vector3f &b)
{
    return sqrt(VectorUtilities::dotProduct(a, b));
}
//Vector 4f

double VectorUtilities::dotProduct(const Vector4f &a, const Vector4f &b)
{
    double scalar = 0;
    for (int i = 0; i < 4; i++)
    {
        scalar += (double)a.vec[i] * b.vec[i];
    }

    return scalar;
}
Vector4f VectorUtilities::normalizeCopy(const Vector4f &v)
{
#ifdef _USESIMDINTRINSICS
    Vector4f vec(v.xyzw);
#else
    Vector4f vec(v.x,v.y,v.z,v.w);
#endif
    
    vec.normalize();
    return vec;
}

double VectorUtilities::Length(const Vector4f &a, const Vector4f &b)
{
    return sqrt(VectorUtilities::dotProduct(a, b));
}