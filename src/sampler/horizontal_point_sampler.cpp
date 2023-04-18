#include "horizontal_point_sampler.h"

std::vector<std::tuple<float, float>> horizontal_point_sampler::generate_points()
{
	std::vector<std::tuple<float, float>> points;
	points.reserve(num_samples);
	for (unsigned int i = 1; i <= num_samples; i++)
	{
		const float val = static_cast<float>(i) / static_cast<float>(num_samples);
		points.emplace_back(val, 0.5f);
	}
	return points;
}
