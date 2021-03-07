#include "VectorUtilities.hpp"
#include <iostream>
Vector3f VectorUtilities::crossProduct(const Vector3f &a, const Vector3f &b)
{

    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
float VectorUtilities::dotProduct(const Vector3f &a, const Vector3f &b)
{
    float scalar = 0;
    for (int i = 0; i < 3; i++)
    {
        scalar += a.vec[i] * b.vec[i];
    }

    return scalar;
}
Vector3f VectorUtilities::normalizeCopy(const Vector3f &v)
{
    Vector3f vec(v.xyz);
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
    float scalar = 0;
    for (int i = 0; i < 4; i++)
    {
        scalar += a.vec[i] * b.vec[i];
    }

    return scalar;
}
Vector4f VectorUtilities::normalizeCopy(const Vector4f &v)
{
    Vector4f vec(v.xyzw);
    vec.normalize();
    return vec;
}

float VectorUtilities::Length(const Vector4f &a, const Vector4f &b)
{
    return sqrt(VectorUtilities::dotProduct(a, b));
}