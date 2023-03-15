#ifndef _MATRIX44_
#define _MATRIX44_
#include "Vector4f.hpp"

class Matrix4x4
{ //using column major order

    float mm44[4][4];

public:
    Matrix4x4();
    Matrix4x4(const float _mm44[4][4]);
    Vector4f operator*(const Vector4f &v) const
    {
        Vector4f vec(0, 0, 0, 0);
        vec.x = mm44[0][0] * v.x + mm44[0][1] * v.y + mm44[0][2] * v.z + mm44[0][3] * v.w;
        vec.y = mm44[1][0] * v.x + mm44[1][1] * v.y + mm44[1][2] * v.z + mm44[1][3] * v.w;
        vec.z = mm44[2][0] * v.x + mm44[2][1] * v.y + mm44[2][2] * v.z + mm44[2][3] * v.w;
        vec.w= mm44[3][0] * v.x + mm44[3][1] * v.y + mm44[3][2] * v.z + mm44[3][3] * v.w;
        return vec;
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

    Matrix4x4 operator*(const Matrix4x4& m44) const
    {
        float temp[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float num = 0;
                for (int k = 0; k < 4; k++)
                {
                    num += m44.mm44[i][k] * mm44[k][j];
                }

                temp[i][j] = num;
            }
        }
        return Matrix4x4(temp);
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

    void loadIdentity();

    void ConcatTransformation(const float _mm[4][4]);
    void ConcatTransformation(const Matrix4x4 &matrix44);
    void ConcatRotateX(float angle);
    void ConcatRotateY(float angle);
    void ConcatRotateZ(float angle);
    void ConcatTranslate(float tx, float ty, float tz);
    void ConcatScale(float x);
    void ConcatScale(float x, float y, float z);
    void ConcatShearx(float Shy,float Shz);
    void ConcatSheary(float Shx,float Shz);
    void ConcatShearz(float Shx,float Shy);
    void ConcatReflect(bool x,bool y,bool z);
    Matrix4x4 Transpose();
    float Determinant();
    //Returns a new Transposed index of this matrix
    Matrix4x4 Transpose(const Matrix4x4 &matrix);
    Matrix4x4 Inverse();
    void printMatrix();
};
#endif