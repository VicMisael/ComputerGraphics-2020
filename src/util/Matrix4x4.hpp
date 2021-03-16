#ifndef _MATRIX44_
#define _MATRIX44_
#include "Vector4f.hpp"
class Matrix4x4
{ //using column major order

    float mm44[4][4];

public:
    Matrix4x4();
    Matrix4x4(float _mm44[4][4]);
    Vector4f operator*(const Vector4f &v) const
    {
        float x = mm44[0][0] * v.x + mm44[0][1] * v.y + mm44[0][2] * v.z + mm44[0][3] * v.w;
        float y = mm44[1][0] * v.x + mm44[1][1] * v.y + mm44[1][2] * v.z + mm44[1][3] * v.w;
        float z = mm44[2][0] * v.x + mm44[2][1] * v.y + mm44[2][2] * v.z + mm44[2][3] * v.w;
        float w = mm44[3][0] * v.x + mm44[3][1] * v.y + mm44[3][2] * v.z + mm44[3][3] * v.w;
        return Vector4f(x, y, z, w);
    }
    Vector3f operator*(const Vector3f &v) const
    {
        Vector3f vec(0, 0, 0);
        vec.x = mm44[0][0] * v.x + mm44[0][1] * v.y + mm44[0][2] * v.z + mm44[0][3];
        vec.y = mm44[1][0] * v.x + mm44[1][1] * v.y + mm44[1][2] * v.z + mm44[1][3];
        vec.z = mm44[2][0] * v.x + mm44[2][1] * v.y + mm44[2][2] * v.z + mm44[2][3];
        float w = mm44[3][0] * v.x + mm44[3][1] * v.y + mm44[3][2] * v.z + mm44[3][3];
        if (w != 1 && w != 0)
        {
            vec.x /= w;
            vec.y /= w;
            vec.z /= w;
        }
        return vec;
    }
    Matrix4x4 operator+(const Matrix4x4 &matrix) const
    {
        float retmm44[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                retmm44[i][j] = mm44[i][j] + matrix.mm44[i][j];
            }
        }
        return Matrix4x4(retmm44);
    }
    Matrix4x4 operator-(const Matrix4x4 &matrix) const
    {
        float retmm44[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                retmm44[i][j] = mm44[i][j] - matrix.mm44[i][j];
            }
        }
        return Matrix4x4(retmm44);
    }

    void ConcatTransformation(const float _mm[4][4]);
    void ConcatTransformation(const Matrix4x4 &matrix44);
    Matrix4x4 Transpose();
    float Determinant();
    //Returns a new Transposed index of this matrix
    Matrix4x4 Transpose(const Matrix4x4 &matrix);
    Matrix4x4 Inverse();
    void printMatrix();
};
#endif