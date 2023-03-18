#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif



Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = -Cx * ((4.0f / 3.0f) / vpw);
    float vy = -Cy * ((3.0f/4.0f) / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
int main(int argc, char** argv)
{

    std::cout << std::thread::hardware_concurrency() << std::endl;
    SDL_Window* win = NULL;
    win = SDL_CreateWindow("RayCaster", 100, 100, screenwidthheight, screenwidthheight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenwidthheight, screenwidthheight);
    bool run = true;
    //auto window = new Color[screenwidthheight][screenwidthheight];
    uint32_t* rgba = new uint32_t[screenwidthheight * screenwidthheight];
    int reflectionDepth = 900;
    float vcx = 4;
    float vcy = 0;
    float vcz = -6;
    int Cw = screenwidthheight;
    int Ch = screenwidthheight;
    bool parallelProjection = true;
    bool shadows = true;
    auto draw = [&]() {
        while (run) {
            Point3f eye = Point3f(vcx, vcy, vcz);
            Point3f at = Point3f(1, 2, 5);
            Point3f up = Point3f(vcx, vcy+12, vcz);
            Camera camera = Camera(eye, at, up);
            World world;
            world.SetShadowsOn(shadows);
            //Get timings
            auto t1 = std::chrono::high_resolution_clock::now();
            uint32_t temprgba = 0;
            const Matrix4x4 invViewMatrix = camera.getCameraToWorld();
            for (int y = -Ch / 2; y < Ch / 2; y++)
            {

                for (int x = -Cw / 2; x < Cw / 2; x++)
                {
                    if (x == 138 && y == -45) {
                        std::cout << "a";
                    }
                    const auto origin = invViewMatrix * Point3f(x / (float)Cw, y / (float)Ch, 0);
                    const auto point = invViewMatrix * canvasToViewport(x, y, Cw, Ch, -1);
                    Ray r = Ray(origin, point-origin);
                    rgba[(y + Ch / 2) * screenwidthheight + (x + Cw / 2)] = world.computeColor(r, 1, reflectionDepth).rgba();
                }
            }
            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms_double = t2 - t1;
            std::cout << ms_double.count() << "ms" << std::endl;
        }
    };
    
    std::thread t(draw);
    while (run)
    {

        SDL_UpdateTexture(framebuffer, NULL, rgba, screenwidthheight * sizeof(uint32_t));
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
                if (e.key.keysym.sym == SDLK_s)
                {
                    shadows = !shadows;
                }
                if (e.key.keysym.sym == SDLK_r) {
                    reflectionDepth++;

                    if (reflectionDepth > 3) {
                        reflectionDepth = 0;
                    }
                }
                if (e.key.keysym.sym == SDLK_p) {
                    parallelProjection = !parallelProjection;
                }
                break;
            case SDL_QUIT:
                //std::cout<<"Sai pora"<<std::endl;
                SDL_RenderClear(renderer);
                SDL_DestroyTexture(framebuffer);
                SDL_DestroyWindow(win);
                SDL_Quit();
                run = false;
                t.join();
                break;
            }
        }
    }
    return 0;
};