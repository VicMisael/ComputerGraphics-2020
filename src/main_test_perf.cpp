#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"

Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = Cx * (1.0 / vpw);
    float vy = -Cy * (1.0 / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}

uint32_t *rgba = new uint32_t[512 * 512];
int main()
{

    double vcup = -1;
    int Cw = 512;
    int Ch = 512;
    World world;
    for (int i = 0; i < 1000; i++)
    {
        for (int y = -Ch / 2; y < Ch / 2; y++)
        {
            for (int x = -Cw / 2; x < Cw / 2; x++)
            {
                Ray r = Ray(canvasToViewport(x, y, Cw, Ch, 1), Point3f(0, 0, 0));
                rgba[(y + Ch / 2) * 512 + (x + Cw / 2)] = world.computeColor(r, 1).rgba;
            }
        }
    }
}