#include "Matrix4x4.hpp"
Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++)
    {
        mm44[i][i] = 1;
    }
}