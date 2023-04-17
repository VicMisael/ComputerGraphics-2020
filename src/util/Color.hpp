#ifndef _COLOR_
#define _COLOR_
#include <cstdint>

class Color
{
private:

public:
	Color(int _r, int _g, int _b);

	Color() : r(0.0f), g(0.0f), b(0.0)
	{
	};
	Color(float _r, float _g, float _b);

	Color(uint8_t color[3]) : Color(color[0], color[1], color[2])
	{
	};
	uint32_t rgba();

	float r{}, g{}, b{};

	Color operator+(const Color& a) const
	{
		Color NewColor;
		return Color(r + a.r, g + a.g, b + a.b);
	}

	Color operator*(const float& a) const
	{
		float components[3];
		components[0] = r * a;
		components[1] = g * a;
		components[2] = b * a;
		return Color(components[0], components[1], components[2]);
	}

	void operator+=(const Color& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
	}
};

#endif
