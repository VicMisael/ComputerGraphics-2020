#ifndef _CONE_
#define _CONE_
#include <cmath>
#include "../util/Vector3f.hpp"
#include "../util/definitions.hpp"
#include "../util/VectorUtilities.hpp"
#include "AABB.h"
#include "BaseObject.hpp"

// Definindo o código do cone
class Cone final : public BaseObject
{
private:
	Point3f center;
	Point3f vertice;
	Vector3f axis;
	float height;
	float radius;
	float cosTheta;
	float cos2Theta;
	AABB aabb;

	//Point3f scale_aux;

public:
	Cone(Vector3f axis, float height, float radius, Color c);
	std::tuple<int, float, Vector3f> Intersects(const Ray& ray);
	void ApplyTransformation() override;
	Vector3f getNormal(Point3f p) override;
	void ApplyCamera(Matrix4x4 mm44) override;
	void computeAABB();
};

#endif
