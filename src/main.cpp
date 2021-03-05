#include "util/Matrix4x4.hpp"
#include <iostream>

int main()
{
    float M4[4][4] = {
        0, 5, 3, 5,
        9, 2, 1, 4,
        4, 0.23, 1, 3,
        1, 2, 3, 4.55};

    Matrix4x4 matrx(M4);
    for (int i; i < 100000; i++)
    {

        matrx.Determinant();
    }
}