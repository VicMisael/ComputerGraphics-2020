#pragma once
#include "sampler.h"

class horizontal_point_sampler :
	public sampler
{
public:
	horizontal_point_sampler(const unsigned int num) : sampler(num)
	{
	}

	std::vector<std::tuple<float, float>> generate_points() final;
};
