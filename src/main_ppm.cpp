#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#include <chrono>

#define screenwidthheight 600
Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = -Cx * (1.0 / vpw);
    float vy = -Cy * (1.0 / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
int main(int argc, char **argv)
{

    //auto window = new Color[512][512];
    uint32_t *rgba = new uint32_t[screenwidthheight * screenwidthheight];
    int reflectionDepth = 3;
    float vcx = 4;
    float vcy = 6;
    float vcz = -6;

    int Cw = screenwidthheight;
    int Ch = screenwidthheight;
    Point3f eye = Point3f(vcx, vcy, vcz);
    Point3f at = Point3f(1, 2, 5);
    Point3f up = Point3f(1, 12, 5);
    Camera camera = Camera(eye, at, up);
    World world(camera);
    world.SetShadowsOn(true);
    std::cout << "P3\n"
              << Ch << ' ' << Cw << "\n255\n";

    // for (int y = -Ch / 2; y < Ch / 2; y++)
    // {
    //     for (int x = -Cw / 2; x < Cw / 2; x++)
    //     {
    //         Ray r = Ray(Point3f(0, 0, 0), canvasToViewport(x, y, Cw, Ch, -1));
    //         Color color = world.computeColor(r, 1, reflectionDepth);
    //         std::cout << ((int)(color.r * 255)) << ' ' << (int)(color.g * 255) << ' ' << (int)(color.b * 255) << '\n';
    //     }
    // }
    for (int y = -Ch / 2; y < Ch / 2; y++)
    {
        for (int x = -Cw / 2; x < Cw / 2; x++)
        {
            float r, g, b;
            r = g = b = 0;
            for (int i = 0; i < SSRate; i++)
            {
                Ray ray = Ray(Point3f(0, 0, 0), canvasToViewport(x + ((float)i / SSRate), y + ((float)i / SSRate), Cw, Ch, -1));
                r += world.computeColor(ray, 1, reflectionDepth).r;
                g += world.computeColor(ray, 1, reflectionDepth).g;
                b += world.computeColor(ray, 1, reflectionDepth).b;
            }
            Color color = Color(r, g, b, SSRate);
            std::cout << ((int)(color.r * 255)) << ' ' << (int)(color.g * 255) << ' ' << (int)(color.b * 255) << '\n';
        }
    }
};