#include "Vector3f.hpp"

namespace VectorUtilities
{
    Vector3f crossProduct(const Vector3f &a, const Vector3f &b);
    float dotProduct(const Vector3f &a, const Vector3f &b);
    float Length(const Vector3f &a, const Vector3f &b);
    Vector3f normalizeCopy(const Vector3f& v);
}