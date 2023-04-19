#pragma once


#include "definitions.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include <glm/geometric.hpp>


namespace VectorUtilities
{
	static Vector3f crossProduct(const Vector3f& a, const Vector3f& b)
	{
		return cross(a, b);
	}

	static float dotProduct(const Vector3f& a, const Vector3f& b)
	{
		return dot(a, b);
	};

	static float Length(const Vector3f& a, const Vector3f& b)
	{
		return glm::sqrt(dot(a, b));
	};

	static Vector3f normalizeCopy(const Vector3f& v)
	{
		return normalize(v);
	};

	static float dotProduct(const Vector4f& a, const Vector4f& b)
	{
		return dot(a, b);
	};

	static float Length(const Vector4f& a, const Vector4f& b)
	{
		return glm::sqrt(dot(a, b));
	};

	static Vector4f normalizeCopy(const Vector4f& v)
	{
		return normalize(v);
	};

	static Vector3f toVector3f(const Vector4f vec)
	{
		const float Epsilon = 10e-10;
		if (fabs(vec.w) <= Epsilon)
		{
			return Point3f(vec.x, vec.y, vec.z);
		}
		return Vector3f(vec.x / vec.w, vec.y / vec.w, vec.z / vec.w);
	}
}

