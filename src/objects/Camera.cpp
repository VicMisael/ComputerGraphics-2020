#include "Camera.hpp"


//up=Vetor para um ponto acima do at
Camera::Camera(Point3f eye, Point3f at, Point3f up)
{
	using namespace VectorUtilities;
	//Klinha
	Vector3f eyeAt = eye - at;
	eyeAt.normalize();
	Vector3f viewUp = up - eye;
	viewUp.normalize();
	Vector3f I = crossProduct( viewUp,eye);
	I.normalize();
	Vector3f J = crossProduct(eyeAt, I);
	cameraToWorld=(new float[4][4]{
		{I.x, I.y, I.z, dotProduct(I,eye )},
		{J.x, J.y, J.z, dotProduct(J,eye)},
		{eyeAt.x, eyeAt.y, eyeAt.z, dotProduct(eyeAt, eye)},
		{0, 0, 0, 1},
	});
}

Matrix4x4 Camera::getCameraToWorld()
{
	return cameraToWorld;
	
}
Matrix4x4 Camera::getWorldToCamera()
{
	(cameraToWorld.Inverse() * cameraToWorld).printMatrix();
	return cameraToWorld.Inverse();
}
