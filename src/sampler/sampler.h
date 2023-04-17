#pragma once
#include<vector>
#include<tuple>

class sampler
{
	sampler();

public:
	const unsigned int num_samples;

	sampler(unsigned const int num) : num_samples(num)
	{
	}
	virtual std::vector<std::tuple<float, float>> generate_points() = 0;
};
