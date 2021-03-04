#include "util/Vector3f.hpp"
#include "util/VectorUtilities.hpp"
#include <iostream>

int main()
{

    Vector3f vec(2, 3, 5);
    std::cout << VectorUtilities::Length(vec, Vector3f(2,3,5)) << std::endl;
    Vector3f vec3(6,9,1);
    std::cout << VectorUtilities::normalizeCopy(vec3).length() << std::endl;
}