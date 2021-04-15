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
    float vx = -Cx * (1.0/ vpw);
    float vy = -Cy * (1.0/ vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
uint32_t *rgba = new uint32_t[512 * 512];
void inline paint(int ystart, int yend, int xstart, int xend, int Cw, int Ch, World  world)
{
    for (int y = ystart; y < yend; y++)
    {
        for (int x = xstart; x < xend; x++)
        {
            Ray r = Ray(Point3f(0,0,0),canvasToViewport(x, y, Cw, Ch, -1));
            rgba[(y + Ch / 2) * Ch + (x + Cw / 2)] = world.computeColor(r, -1,1).rgba();
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
    float vcx=0;
    float vcy = 3;
    float vcz = -6;
    int Cw = 512;
    int Ch = 512;

    while (run)
    {
        Point3f eye = Point3f(vcx,vcy,vcz);
        Point3f at = Point3f(0, 0 , 5);
        Point3f up = Point3f(0, 6,5);
        Camera camera = Camera(eye, at, up);
        World world(camera);
        World world2(camera);
        World world3(camera);
        World world4(camera);
        //Section1 y:-Ch/2->0 x: -Cw/2->0,First quarter
        std::thread t1(paint, -Ch / 2, 0, -Cw / 2, 0, Cw, Ch, world);
        //Section2:y:-Ch/2->0 x: 0->Cw/2,Second Quarter
        std::thread t2(paint, -Ch / 2, 0, 0, Cw / 2, Cw, Ch, world2);
        //Section3 y:0->Ch/2 x: -Cw/2->0,First quarter
        std::thread t3(paint, 0, Ch / 2, -Cw / 2, 0, Cw, Ch, world3);
        //Section4:y:0->Ch/2 x: 0->Cw/2,Second Quarter
        std::thread t4(paint, 0, Ch / 2, 0, Cw / 2, Cw, Ch, world4);
        //Teste
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        std::cout << "X: " << (vcx) << "Y: " << vcy << "Z: " << (vcz+=0.1) << std::endl;
        SDL_UpdateTexture(framebuffer, NULL, rgba, 512 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                if (e.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    vcx += 0.01;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    vcx -= 0.01;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                    vcz -= 0.01;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                    vcz += 0.01;
                }
                if (e.key.keysym.sym == SDLK_a)
                {
                    vcy -= 0.01;
                }
                if (e.key.keysym.sym == SDLK_d)
                {
                    vcy += 0.01;
                }
                break;
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