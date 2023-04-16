#include "Color.hpp"
#include <cmath>


Color::Color(int _r, int _g, int _b)
{
	this->r = _r / 255.0;
	this->g = _g / 255.0;
	this->b = _b / 255.0;
}
Color::Color(float _r, float _g, float _b) {
	this->r = _r;
	this->g = _g;
	this->b = _b;
}

uint32_t Color::rgba()
{
	union {
		uint32_t rgba;
		struct {
			uint8_t  _r, _g, _b, _a;
		};
	} rgbaCol;
	using namespace std;
	
	
	

	rgbaCol._r = (r > 1 ? 1 : r) * 255;
	rgbaCol._g = (g > 1 ? 1 : g) * 255;
	rgbaCol._b = (b > 1 ? 1 : b) * 255;
	rgbaCol._a = 255;
	return rgbaCol.rgba;
}
