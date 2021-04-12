#include "Camera.hpp"


//up=Vetor para um ponto acima do at
Camera::Camera(Point3f eye, Point3f at, Point3f up)
{
	using namespace VectorUtilities;
	this->Eye = &eye;
	//Klinha
	Vector3f k = eye - at;
	k.normalize();
	Vector3f viewUp = up - eye;
	viewUp.normalize();
	Vector3f I = crossProduct( viewUp,eye);
	I.normalize();
	Vector3f J = crossProduct(k, I);
	J.normalize();
	cameraToWorld=Matrix4x4(new float[4][4]{
		{I.x, I.y, I.z,-1.0f*dotProduct(I,eye)},
		{J.x, J.y, J.z,-1.0f*dotProduct(J,eye)},
		{k.x, k.y, k.z,-1.0f*dotProduct(k,eye)},
		{0, 0, 0, 1},
	});
	//cameraToWorld.printMatrix();

}

Matrix4x4 Camera::getCameraToWorld()
{
	return cameraToWorld;
	
}
Matrix4x4 Camera::getWorldToCamera()
{
	//cameraToWorld.Inverse().printMatrix();
	return cameraToWorld.Inverse();
}

Point3f Camera::getEyePosition()
{
	return *Eye;
}

