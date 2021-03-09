#include "util/Matrix3x3.hpp"
#include <iostream>

int main()
{
    float M4[3][3] = {
        12, -5, 3,
        9, 1, 1,
        4, 0, 1,};
       

    Matrix3x3 matrx(M4);
    std::cout << matrx.Determinant() << std::endl;
    matrx.printMatrix();
    Matrix3x3 inv = matrx.Inverse();
    inv.printMatrix();
    matrx.ConcatTransformation(inv);
    matrx.printMatrix();
    // matrx.ConcatTransformation(inv);
    // matrx.printMatrix(); // std::cout << matrx.Determinant() << std::endl;
}