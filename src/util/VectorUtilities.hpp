#include "Vector3f.hpp"
#include "Vector4f.hpp"
namespace VectorUtilities
{
    Vector3f crossProduct(const Vector3f &a, const Vector3f &b);
    double dotProduct(const Vector3f &a, const Vector3f &b);
    double Length(const Vector3f &a, const Vector3f &b);
    Vector3f normalizeCopy(const Vector3f &v);

    double dotProduct(const Vector4f &a, const Vector4f &b);
    double Length(const Vector4f &a, const Vector4f &b);
    Vector4f normalizeCopy(const Vector4f &v);
}