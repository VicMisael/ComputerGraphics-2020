#include "util/Matrix3x3.hpp"
#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

int main(int argc, char **argv)
{
    SDL_DisplayMode DM;
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("RayCaster", 1920/2 , 1080/2, 512, 512, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 512, 512);
    bool run = true;
    auto window = new Color[512][512];
    uint32_t *rgba = new uint32_t[512 * 512];
    World world;
    float vc=0;
    while (run)
    {
        
        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {
                float vx = (float)x * (1.0 / 512);
                float vy = (float)y * (1.0 / 512);
                float vz = 1;
               
                Ray r=Ray(Point3f(vx, vy,vz ), Point3f(0, vc, 0));
                window[x][y]= world.computeColor(r);
          
            }
      
        }
        if (vc <= 1) {
            vc += 0.001;
        }

        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {

                rgba[y * 512 + x] = window[x][y].rgba;
                
            }
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
            case SDL_KEYDOWN:
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
       // std::cout <<"P6 512 512 255 ";

       /* for (int x = 0; x < 512 ; x++)
        {
            for (int y = 0; y < 512; y++)
            {
                std::cout << window[x][y].r << window[x][y].g << window[x][y].b;
            }
        }
        run=false;*/
    }
    return 0;
};