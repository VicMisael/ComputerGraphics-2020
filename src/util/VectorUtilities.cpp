/*
#include "VectorUtilities.hpp"
#include <glm/geometric.hpp>


Vector3f VectorUtilities::crossProduct(const Vector3f& a, const Vector3f& b) {
    return glm::cross(a, b);
}
float VectorUtilities::dotProduct(const Vector3f& a, const Vector3f& b) {
    return glm::dot(a, b);
};
float  VectorUtilities::Length(const Vector3f& a, const Vector3f& b) {
    return glm::sqrt(glm::dot(a, b));
};
Vector3f  VectorUtilities::normalizeCopy(const Vector3f& v) {
    return glm::normalize(v);
};

float VectorUtilities::dotProduct(const Vector4f& a, const Vector4f& b) {
    return glm::dot(a, b);
};
float VectorUtilities::Length(const Vector4f& a, const Vector4f& b) {
    return glm::sqrt(glm::dot(a, b));
};
Vector4f VectorUtilities::normalizeCopy(const Vector4f& v) {
    return glm::normalize(v);
};

Vector3f VectorUtilities::toVector3f(const Vector4f vec) {
    const float Epsilon = 10e-10;
    if (fabs(vec.w) <= Epsilon) {
        return Point3f(vec.x, vec.y, vec.z);
    }
    return Vector3f(vec.x / vec.w, vec.y / vec.w, vec.z / vec.w);
}

*/