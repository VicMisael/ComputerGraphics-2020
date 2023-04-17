#include "random_point_sampler.h"

inline std::tuple<float, float> random_point_sampler::generate_random_point()
{
	return {dis(generator), dis(generator)};
}

std::vector<std::tuple<float, float>> random_point_sampler::generate_points()
{
	std::vector<std::tuple<float, float>> points;
	points.reserve(num_samples);
	for (unsigned int i = 0; i < num_samples; i++)
	{
		points.emplace_back(generate_random_point());
	}
	return points;
}
