#pragma once
#include "sampler.h"

class equidistant_point_sampler : public sampler
{
public:
	equidistant_point_sampler(const unsigned int val): sampler(val)
	{
	}

	std::vector<std::tuple<float, float>> generate_points() override;
};
