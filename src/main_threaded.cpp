#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#include <thread>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = Cx * (1.0 / vpw);
    float vy = -Cy * (1.0 / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
uint32_t *rgba = new uint32_t[512 * 512];
void paint(int ystart, int yend, int xstart, int xend, int Cw, int Ch, World world, float vcup)
{
    for (int y = ystart; y < yend; y++)
    {
        for (int x = xstart; x < xend; x++)
        {
            Ray r = Ray(canvasToViewport(x, y, Cw, Ch, vcup), Point3f(0, 0, 0));
            rgba[(y + Ch / 2) * Ch + (x + Cw / 2)] = world.computeColor(r, vcup).rgba;
        }
    }
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

    double vcup = -1;
    int Cw = 512;
    int Ch = 512;
    World world;

    while (run)
    {

        //Section1 y:-Ch/2->0 x: -Cw/2->0,First quarter
        std::thread t1(paint, -Ch / 2, 0, -Cw / 2, 0, Cw, Ch, world, vcup);
        //Section2:y:-Ch/2->0 x: 0->Cw/2,Second Quarter
        std::thread t2(paint, -Ch / 2, 0, 0, Cw / 2, Cw, Ch, world, vcup);
        //Section3 y:0->Ch/2 x: -Cw/2->0,First quarter
        std::thread t3(paint, 0, Ch / 2, -Cw / 2, 0, Cw, Ch, world, vcup);
        //Section4:y:0->Ch/2 x: 0->Cw/2,Second Quarter
        std::thread t4(paint, 0, Ch / 2, 0, Cw / 2, Cw, Ch, world, vcup);
        //Teste
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        std::cout << (vcup += 0.01) << std::endl;
        if (vcup > 1)
        {
            vcup = 0;
        }
        SDL_UpdateTexture(framebuffer, NULL, rgba, 512 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                //std::cout<<"Sai pora"<<std::endl;
                SDL_RenderClear(renderer);
                SDL_DestroyTexture(framebuffer);
                SDL_DestroyWindow(win);
                SDL_Quit();
                run = false;
                break;
            }
        }
    }
    return 0;
};