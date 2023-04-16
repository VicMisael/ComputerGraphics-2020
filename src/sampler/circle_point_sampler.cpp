#include "circle_point_sampler.h"

inline std::tuple<float, float> circle_point_sampler::generate_random_point()
{
    constexpr float center_x_y = 0.5f;


    return { center_x_y + dis(generator),center_x_y + dis(generator) };
}
std::vector<std::tuple<float, float>> circle_point_sampler::generate_points()
{
    std::vector<std::tuple<float, float>> points;
    points.reserve(num_samples);
    for (int i = 1; i <= num_samples; i++) {
        points.emplace_back(generate_random_point());
    }
    return points;
}
