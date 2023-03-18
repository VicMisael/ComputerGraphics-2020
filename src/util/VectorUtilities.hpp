#ifndef _VECTOR_UTILITIES_
#define _VECTOR_UTILITIES_


#include "definitions.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include <glm/geometric.hpp>


namespace VectorUtilities
{
    static Vector3f  crossProduct(const Vector3f& a, const Vector3f& b) {
        return glm::cross(a,b);
    }
    static float dotProduct(const Vector3f& a, const Vector3f& b) {
        return glm::dot(a, b);
    };
    static float  Length(const Vector3f& a, const Vector3f& b) {
        return glm::sqrt(glm::dot(a,b));
    };
    static Vector3f  normalizeCopy(const Vector3f& v) {
        /*float sqrdlength = v.x * v.x + v.y * v.y + v.z * v.z;

        float x = v.x*glm::inversesqrt(sqrdlength);
        float y = v.y*glm::inversesqrt(sqrdlength);
        float z = v.z*glm::inversesqrt(sqrdlength);
        return Vector3f(x, y, z);
        */   

        return glm::normalize(v);
    };

    static float dotProduct(const Vector4f& a, const Vector4f& b) {
        return glm::dot(a, b);
    };
    static float Length(const Vector4f& a, const Vector4f& b) {
        return glm::sqrt(glm::dot(a, b));
    };
    static Vector4f normalizeCopy(const Vector4f& v) {
        return glm::normalize(v);
    };

    static Vector3f toVector3f(const Vector4f vec) {
        const float Epsilon = 10e-10;
        if (fabs(vec.w) <= Epsilon) {
            return Point3f(vec.x, vec.y, vec.z);
        }
        return Vector3f(vec.x / vec.w, vec.y / vec.w, vec.z / vec.w);
    }

}

#endif