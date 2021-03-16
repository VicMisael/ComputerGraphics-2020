#include "util/Matrix3x3.hpp"
#include <iostream>

int main()
{
    Vector3f vec(1, 0, 0);

    for (int x = 0; x < 1920; x++)
    {
        for (int y = 0; y < 1080; y)
        {
            Matrix3x3 m33;
            m33.ConcatRotateZ(PI / 2);
            //m33.printMatrix();
            Vector3f vec2 = m33 * vec;
            //  std::cout << "X: " << vec2.x << " Y: " << vec2.y << " Z: " << vec2.z << std::endl;
            Matrix3x3 inv = m33.Inverse();
            Vector3f vec3 = inv * vec;
            //std::cout << "X: " << vec3.x << " Y: " << vec3.y << " Z: " << vec3.z << std::endl;
        }
    }
    // matrx.ConcatTransformation(inv);
    // matrx.printMatrix(); // std::cout << matrx.Determinant() << std::endl;
}