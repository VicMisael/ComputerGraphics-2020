#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#define screenwidthheight 640

Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
    float vx = -Cx * (1.0/ vpw);
    float vy = -Cy * (1.0/ vph);
    float vz = d;
    return Point3f(vx, vy, vz);
}
int main(int argc, char **argv)
{

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("RayCaster", 100, 100, screenwidthheight, screenwidthheight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenwidthheight, screenwidthheight);
    bool run = true;
    //auto window = new Color[screenwidthheight][screenwidthheight];
    uint32_t *rgba = new uint32_t[screenwidthheight * screenwidthheight];
    int reflectionDepth=1;
    float vcx=0;
    float vcy = 0;
    float vcz = -6;
    int Cw = screenwidthheight;
    int Ch = screenwidthheight;
    
    bool shadows = true;
    while (run)
    {
        Point3f eye = Point3f(vcx,vcy,vcz);
        Point3f at = Point3f(0, 0 , 5);
        Point3f up = Point3f(0, 6,5);
        Camera camera = Camera(eye, at, up);
        World world(camera);
        world.SetShadowsOn(shadows);
        for (int y = -Ch / 2; y < Ch / 2; y++)
        {

            for (int x = -Cw / 2; x < Cw / 2; x++)
            {
                //Orthographic
                //Ray r = Ray(Point3f(0,0,0),Vector3f(0,0,-1),1);
                //Perspective
                //CanvasEye=Ray origin
                #ifndef _SUPERSAMPLE_
                Ray r = Ray(Point3f(0,0,0),canvasToViewport(x, y, Cw, Ch, -1));
                rgba[(y + Ch / 2) * screenwidthheight + (x + Cw / 2)] = world.computeColor(r, 1,1).rgba();
                #else
                float r,g,b;
                r=g=b=0;
                for(int i=0;i<SSRate;i++){
                    Ray ray = Ray(Point3f(0,0,0),canvasToViewport(x+((float)i/SSRate), y+((float)i/SSRate), Cw, Ch, -1));
                    r+=world.computeColor(ray, 1,reflectionDepth).r;
                    g+=world.computeColor(ray, 1,reflectionDepth).g;
                    b+=world.computeColor(ray, 1,reflectionDepth).b;
                }
                rgba[(y + Ch / 2) * screenwidthheight + (x + Cw / 2)] =Color(r,g,b,SSRate).rgba();
                #endif
            }
        }
        std::cout <<"X: "<< (vcx)<<"Y: "<<vcy<<"Z: "<<vcz << std::endl;
        if (vcx < 7) {
            vcx += 0.3;
        }
        if (vcy < 15) {
            vcy += 0.5;
        }
        vcz+=0.1;
        if (vcz > 10) {
            vcz = -12;
        }
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
        //return 1;
    }
    return 0;
};