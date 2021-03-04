#include "Vector3f.hpp"
#include "Vector4f.hpp"
namespace VectorUtilities
{
    Vector3f crossProduct(const Vector3f &a, const Vector3f &b);
    float dotProduct(const Vector3f &a, const Vector3f &b);
    float Length(const Vector3f &a, const Vector3f &b);
    Vector3f normalizeCopy(const Vector3f &v);

    Vector4f crossProduct(const Vector4f &a, const Vector4f &b);
    float dotProduct(const Vector4f &a, const Vector4f &b);
    float Length(const Vector4f &a, const Vector4f &b);
    Vector4f normalizedCopy(const Vector4f &v);
}