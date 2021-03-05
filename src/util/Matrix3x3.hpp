#ifndef _MATRIX33_
#define _MATRIX33_
#include "Vector3f.hpp"
class Matrix3x3
{
    float mm33[3][3];
    //Inits a 3x3 matrix
public:
    Matrix3x3();
    Matrix3x3(float _mm33[3][3]);
    Vector3f operator*(const Vector3f &v) const
    {
        float x = mm33[0][0] * v.x + mm33[0][1] * v.y + mm33[0][2] * v.z;
        float y = mm33[1][0] * v.x + mm33[1][1] * v.y + mm33[1][2] * v.z;
        float z = mm33[2][0] * v.x + mm33[2][1] * v.y + mm33[2][2] * v.z;
        return Vector3f(x, y, z);
    }
    Matrix3x3 operator+(const Matrix3x3 &matrix) const
    {
        float retmm33[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                retmm33[i][j] = mm33[i][j] + matrix.mm33[i][j];
            }
        }
        return Matrix3x3(retmm33);
    }
    Matrix3x3 operator-(const Matrix3x3 &matrix) const
    {
        float retmm33[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                retmm33[i][j] = mm33[i][j] - matrix.mm33[i][j];
            }
        }
        return Matrix3x3(retmm33);
    }
};
#endif