#include "vertical_point_sampler.h"

std::vector<std::tuple<float, float>> vertical_point_sampler::generate_points()
{
	std::vector<std::tuple<float, float>> points;
	points.reserve(num_samples);
	for (unsigned int i = 1; i <= num_samples; i++)
	{
		const float val = static_cast<float>(i) / static_cast<float>(num_samples);
		points.emplace_back(std::tuple(0, val));
	}
	return points;
}
