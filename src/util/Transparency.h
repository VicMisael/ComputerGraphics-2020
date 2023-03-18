#pragma once
struct Transparency {
	float transparency;
	float refraction;
public:
	Transparency() :Transparency(0, 0) {};
	Transparency(float transparency, float refraction)  {
		this->transparency = transparency;
		this->refraction = refraction;
	}
};