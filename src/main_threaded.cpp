#include <iostream>
#include "util/Color.hpp"
#include "objects/World.hpp"
#include "util/Ray.hpp"
#include <chrono>
#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <random>
#include <glm/ext/matrix_transform.hpp>

#include "sampler/diagonal_point_sampler.h"
#include "sampler/equidistant_point_sampler.h"
#include "sampler/mt19937_point_sampler.h"
#include "sampler/random_point_sampler.h"
#include "sampler/vertical_point_sampler.h"
#include "sampler/horizontal_point_sampler.h"

Point3f inline canvasToViewport(float Cx, float Cy, int vpw, int vph, float d)
{
	const float vx = Cx * ((vph / static_cast<float>(vpw)) / vpw);
	const float vy = Cy * ((vpw / static_cast<float>(vph)) / vph);
	const float vz = d;
	//std::cout << "X: " << vx << "Y:" << vy << std::endl;
	return Point3f(vx, vy, vz);
}

int main(int argc, char** argv)
{
	std::cout << std::thread::hardware_concurrency() << std::endl;
	SDL_Window* win = nullptr;
	win = SDL_CreateWindow("RayCaster", 100, 100, screenwidthheight, screenwidthheight, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
	                                             screenwidthheight, screenwidthheight);
	bool run = true;
	//auto window = new Color[screenwidthheight][screenwidthheight];
	auto rgba = new uint32_t[screenwidthheight * screenwidthheight];
	unsigned int reflectionDepth = 4;
	float vcx = 6;
	float vcy = 0;
	float vcz = -16;
	int Cw = screenwidthheight;
	int Ch = screenwidthheight;
	bool shadows = true;
	const uint32_t numsamples = 16;
	sampler* sampler = new equidistant_point_sampler(numsamples);
	auto draw = [&]()
	{
		while (run)
		{
			auto eye = Point3f(vcx, vcy, vcz);
			auto at = Point3f(6, 3, 2);
			auto up4 = Point4f(0.0f, 1.0f, 0.0f, 0.0f);
			Point3f up = up4.xyz;
			auto camera = Camera(eye, at, up);
			World world(camera);
			world.SetShadowsOn(shadows);
			//Get timings
			auto t1 = std::chrono::high_resolution_clock::now();
			//const Matrix4x4 invViewMatrix = camera.getCameraToWorld();
			for (int y = -Ch / 2; y < Ch / 2; y++)
			{
				for (int x = -Cw / 2; x < Cw / 2; x++)
				{
					Color color;
					const auto& points = sampler->generate_points();
					for (const std::tuple<float, float>& sample_point : points)
					{
						constexpr auto origin = Point3f(0, 0, 0);
						const auto [x_sample, y_sample] = sample_point;
						const auto point = canvasToViewport(x + x_sample, y + y_sample, Cw, Ch, 1);
						auto r = Ray(origin, origin - point);
						color += world.computeColor(r, 1, reflectionDepth);
					}
					color = color * (1.0f / numsamples);
					rgba[(y + Ch / 2) * screenwidthheight + (x + Cw / 2)] = color.rgba();
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
		SDL_UpdateTexture(framebuffer, nullptr, rgba, screenwidthheight * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, framebuffer, nullptr, nullptr);
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
				if (e.key.keysym.sym == SDLK_r)
				{
					reflectionDepth++;

					if (reflectionDepth > 3)
					{
						reflectionDepth = 0;
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
				t.join();
				break;
			}
		}
	}
	return 0;
};
