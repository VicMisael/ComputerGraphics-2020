#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{

    auto window = new Color[512][512];
    Vector3f vec(1,0,1);
    Matrix3x3 mm;
    auto vecs =new Vector3f[512 * 512];
    for (int x = 0; x < 512; x++)
    {
        for (int y = 0; y < 512; y++)
        {
        
            //std::cout << std::dec << "x:" << x << "y:" << y << "  " << std::hex << window[x][y].rgba << std::endl;
        }
    }
    // u_int32_t_
    // SDL_Texture* fb;
}