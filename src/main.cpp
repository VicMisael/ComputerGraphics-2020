#include "util/Vector3f.hpp"
#include "util/VectorUtilities.hpp"
#include <iostream>

int main()
{

    Vector3f vec(2, 3, 5);
    std::cout << VectorUtilities::Length(vec, Vector3f(2,3,5)) << std::endl;
    for(int i=0;i<1000;i++)
        std::cout << VectorUtilities::normalizeCopy(Vector3f(15*i/1000,89,23)).length() << std::endl;
}