#include "util/Matrix4x4.hpp"
#include <iostream>

int main()
{
    float M4[4][4] = {
        0, 0, 3, 5,
        9, 2, 1, 4,
        4, 0, 1, 3,
        1, 2, 3, 4};

    Matrix4x4 matrx(M4);
    std::cout << matrx.Determinant() << std::endl;
    //Matrix4x4 inv = matrx.Inverse();
    //matrx.ConcatTransformation(inv);
    matrx.printMatrix(); // std::cout << matrx.Determinant() << std::endl;

    float Matrixtest[4][4] = {
        1, 0, 0, 5,
        9, 2, 1, 4,
        4, 6, 1, 3,
        1, 2, 3, 4};
    Matrix4x4 NewMatrix(Matrixtest);

    //NewMatrix.ConcatTransformation(matrx);
    NewMatrix.printMatrix();
    //std::cout << NewMatrix.Determinant() << std::endl;
    NewMatrix.Inverse().printMatrix();
}