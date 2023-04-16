#pragma once
#include "sampler.h"
#include <random>
class random_point_sampler:public sampler
{
	
	std::default_random_engine generator;
	std::uniform_real_distribution<float> dis;
	std::tuple<float, float> generate_random_point();
public:
	random_point_sampler(const unsigned int num) :sampler(num), dis(0.0,1.0f){
	};

	std::vector<std::tuple<float, float>> generate_points() override final;
};

