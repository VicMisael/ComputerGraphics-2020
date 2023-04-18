#define SDL_MAIN_HANDLED
#include <tuple>
#include <SDL2/SDL.h>

#include "equidistant_point_sampler.h"
#include "diagonal_point_sampler.h"
#include "mt19937_point_sampler.h"
#include "random_point_sampler.h"
#include "vertical_point_sampler.h"
#include "horizontal_point_sampler.h"
constexpr int screenwidthheight = 400;
int _main(int argc, char** argv)
{
	bool run = true;
	SDL_Window* win = nullptr;
	win = SDL_CreateWindow("Sampler", 100, 100, screenwidthheight, screenwidthheight, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
		screenwidthheight, screenwidthheight);
	while (run) {


		int Cw = screenwidthheight;
		int Ch = screenwidthheight;
		const auto rgba = new uint32_t[screenwidthheight * screenwidthheight];
		constexpr int numsamples = 90;
		sampler* sampler = new diagonal_point_sampler(numsamples);

		const auto& points = sampler->generate_points();
		for (uint16_t y = 0; y < Ch; y++) {
			for (uint16_t x = 0; x < Cw; x++)
			{
				rgba[(y)*screenwidthheight + (x)] = 0;
			}
		}
		for (const std::tuple<float, float>& sample_point : points)
		{
			const auto [x_sample, y_sample] = sample_point;
			uint16_t y = static_cast<uint16_t>(floor(Ch * y_sample));
			uint16_t x = static_cast<uint16_t>(floor(Cw * x_sample));
			rgba[(y)*screenwidthheight + (x)] = 0xffffff;
		}

		SDL_UpdateTexture(framebuffer, nullptr, rgba, screenwidthheight * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, framebuffer, nullptr, nullptr);
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
}
