
#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include "definitions.hpp"
#ifdef _USESIMDINTRINSICS
//#include <intrin.h>
#include <smmintrin.h>
#endif
namespace VectorUtilities
{
    Vector3f  crossProduct(const Vector3f &a, const Vector3f &b);
    float dotProduct(const Vector3f &a, const Vector3f &b);
    float  Length(const Vector3f &a, const Vector3f &b);
    Vector3f  normalizeCopy(const Vector3f &v);

    float dotProduct(const Vector4f &a, const Vector4f &b);
    float Length(const Vector4f &a, const Vector4f &b);
    Vector4f normalizeCopy(const Vector4f &v);
}