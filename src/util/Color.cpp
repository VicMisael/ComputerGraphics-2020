#include "Color.hpp"

Color::Color(uint8_t color[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->color[i] = color[i];
	}
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}