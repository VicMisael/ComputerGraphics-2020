#include "equidistant_point_sampler.h"
#include <cmath>

std::vector<std::tuple<float, float>> equidistant_point_sampler::generate_points()
{
	const unsigned int num_samples_sqrt = static_cast<int>(floor(sqrt(num_samples)));
	std::vector<std::tuple<float, float>> points;
	points.reserve(num_samples);
	if (num_samples_sqrt * num_samples_sqrt < num_samples)
	{
		const unsigned int missing = num_samples - num_samples_sqrt * num_samples_sqrt;
		for (unsigned int i = 1; i <= missing; i++)
		{
			const float val = static_cast<float>(i) / static_cast<float>(missing);
			points.emplace_back(std::tuple(val, val));
		}
	}

	for (unsigned int i = 1; i <= num_samples_sqrt; i++)
	{
		for (unsigned int j = 1; j <= num_samples_sqrt; j++)
		{
			const float val_x = static_cast<float>(j) / static_cast<float>(num_samples_sqrt);
			const float val_y = static_cast<float>(i) / static_cast<float>(num_samples_sqrt);
			points.emplace_back(std::tuple(val_x, val_y));
		}
	}
	return points;
}
