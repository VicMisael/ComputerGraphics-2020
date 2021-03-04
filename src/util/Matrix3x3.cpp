#include "Matrix3x3.hpp"
Matrix3x3::Matrix3x3()
{
    for (int i = 0; i < 3; i++)
    {
        mm33[i][i] = 1;
    }
}