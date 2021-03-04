#ifndef _MATRIX44_
#define _MATRIX44_
#include "Vector4f.hpp"
class Matrix4x4
{
    float mm44[4][4];
    Matrix4x4();
    Vector4f operator*(const Vector4f &v) const
    {
        float x = mm44[0][0] * v.x + mm44[0][1] * v.y + mm44[0][2] * v.z + mm44[0][3] * v.w;
        float y = mm44[1][0] * v.x + mm44[1][1] * v.y + mm44[1][2] * v.z + mm44[1][3] * v.w;
        float z = mm44[2][0] * v.x + mm44[2][1] * v.y + mm44[2][2] * v.z + mm44[2][3] * v.w;
        float w = mm44[0][0] * v.x + mm44[0][1] * v.y + mm44[0][2] * v.z + mm44[3][3] * v.w;
        return Vector4f(x, y, z, w);
    }
};
#endif