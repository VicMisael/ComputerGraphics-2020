#include "util/Matrix3x3.hpp"
#include <iostream>

int main()
{
    Vector3f vec(1, 0, 0);
    Matrix3x3 m33;
    m33.ConcatRotateZ(PI/2);
    m33.printMatrix();
    Vector3f vec2 = m33 * vec;
    std::cout << "X: " << vec2.x << " Y: " << vec2.y << " Z: " << vec2.z << std::endl;
    // matrx.ConcatTransformation(inv);
    // matrx.printMatrix(); // std::cout << matrx.Determinant() << std::endl;
}