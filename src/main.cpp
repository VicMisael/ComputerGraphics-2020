#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = -Cx * (1.0 / vpw);
    float vy = -Cy * (1.0 / vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
int main(int argc, char **argv)
{

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("RayCaster", 1920 / 2, 1080 / 2, 800, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);
    bool run = true;
    //auto window = new Color[512][512];
    uint32_t *rgba = new uint32_t[800 * 800];
  
    float vcx=0;
    float vcy = 0.05;
    float vcz = -4.16;
    int reflectionDepth=1;
    int Cw = 800;
    int Ch = 800;
    
    bool shadows = true;
    while (run)
    {
        Point3f eye = Point3f(vcx,vcy,vcz);
        Point3f at = Point3f(0, 0, 2);
        Point3f up = Point3f(0, 2, 2);
        Camera camera = Camera(eye, at, up);
        World world(camera);
        world.SetShadowsOn(shadows);
        Point3f canvasEye = camera.getWorldToCamera() * eye;
        for (int y = -Ch / 2; y < Ch / 2; y++)
        {

            for (int x = -Cw / 2; x < Cw / 2; x++)
            {

                Ray r = Ray(canvasToViewport(canvasEye.x+x, canvasEye.y+y, Cw, Ch, -1),canvasEye);
                rgba[(y + Ch / 2) * 800 + (x + Cw / 2)] = world.computeColor(r, -1,reflectionDepth).rgba();
            }
        }
        std::cout <<"X: "<< (vcx)<<"Y: "<<vcy<<"Z: "<<vcz << std::endl;
        SDL_UpdateTexture(framebuffer, NULL, rgba, 800 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
            if(e.key.keysym.scancode==SDL_SCANCODE_UP){
                    vcx+=0.01;
            }
            if(e.key.keysym.scancode==SDL_SCANCODE_DOWN){
                    vcx-=0.01;
            }
            if(e.key.keysym.scancode==SDL_SCANCODE_LEFT){
                    vcz-=0.01;
            }
            if(e.key.keysym.scancode==SDL_SCANCODE_RIGHT){
                    vcz+=0.01;
            }
            if(e.key.keysym.sym==SDLK_a){
                vcy-=0.01;
            }
            if(e.key.keysym.sym==SDLK_d){
                vcy+=0.01;
            }
            if (e.key.keysym.sym == SDLK_s) {
                shadows = !shadows;
            }
            if(e.key.keysym.sym==SDLK_r){
                reflectionDepth++;
                if(reflectionDepth>1){
                    reflectionDepth=0;
                }
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