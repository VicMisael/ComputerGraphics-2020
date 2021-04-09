#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"


Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = Cx * (1.0 / vpw);
    float vy = Cy * (1.0 / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
int main(int argc, char **argv)
{

    SDL_DisplayMode DM;
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("RayCaster", 1920 / 2, 1080 / 2, 512, 512, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 512, 512);
    bool run = true;
    //auto window = new Color[512][512];
    uint32_t *rgba = new uint32_t[512 * 512];
   
    double vcup = -0.2;
    int Cw = 512;
    int Ch = 512;
    

    while (run)
    {
        Point3f eye = Point3f(0,vcup , 0);
        Camera camera = Camera(eye, Point3f(0, 0, -6), Point3f(0,5 , -6));
        World world(camera);
        for (int y = -Ch / 2; y < Ch / 2; y++)
        {
            for (int x = -Cw / 2; x < Cw / 2; x++)
            {
                Ray r = Ray(canvasToViewport(x, y, Cw, Ch, -1), eye);
                rgba[(y + Ch / 2) * 512 + (x + Cw / 2)] = world.computeColor(r, -1).rgba();
            }
        }
};