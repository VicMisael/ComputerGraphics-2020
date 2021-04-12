#include "BaseObject.hpp"

Color BaseObject::getColor(){

    return c;
}



void BaseObject::setSpecular(float specular)
{
	this->specular = specular;
}

float BaseObject::getSpecular()
{
	return specular;
}

void BaseObject::Translate(float x, float y, float z)
{
	transFMat.ConcatTranslate(x, y, z);
}

void BaseObject::RotateX(float angle)
{
	transFMat.ConcatRotateX(angle);
}

void BaseObject::RotateY(float angle)
{
	transFMat.ConcatRotateY(angle);
}

void BaseObject::RotateZ(float angle)
{
	transFMat.ConcatRotateZ(angle);
}

void BaseObject::Scale(float factor)
{
	transFMat.ConcatScale(factor);
}

void BaseObject::LoadIdentity()
{
	transFMat.loadIdentity();
}

float BaseObject::getTmin()
{
	return t_min;
}

Vector3f BaseObject::getNormal(Point3f p){
	return Vector3f(0,1,0);
}

