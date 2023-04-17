#ifndef _CAMERA_
#define _CAMERA_
#include "../util/Matrix4x4.hpp"
#include "../util/VectorUtilities.hpp"

class Camera
{
private:
	Matrix4x4 worldToCamera;
	Point3f* at = nullptr;
	Point3f* Eye = nullptr;

public:
	Camera() : Camera(Point3f(0, 0, 0), Point3f(0, 0, 0), Point3f(0, 0, 0))
	{
	};
	Camera(Point3f eye, Point3f at, Point3f up);
	Matrix4x4 getCameraToWorld();
	Matrix4x4 getWorldToCamera();
	Point3f getEyePosition();
	Point3f getAt();
};
#endif
