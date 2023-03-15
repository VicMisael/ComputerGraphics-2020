#include "BaseObject.hpp"

Color BaseObject::getColor(){

    return c;
}



BaseObject::BaseObject()
{
	//Null Object
}

void BaseObject::setSpecular(float specular)
{
	this->specular = specular;
}

float BaseObject::getSpecular()
{
	return specular;
}

float BaseObject::getReflectivness()
{
	return reflectiveness;
}

void BaseObject::setReflectivness(float r)
{
	this->reflectiveness=r;
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

void BaseObject::Scale(float x, float y, float z)
{
	transFMat.ConcatScale(x,y,z);
}

void BaseObject::Shearx(float Shy, float Shz)
{
	transFMat.ConcatShearx(Shy, Shz);
}

void BaseObject::Sheary(float Shx, float Shz)
{
	transFMat.ConcatSheary(Shx, Shz);
}

void BaseObject::Shearz(float Shx, float Shy)
{
	transFMat.ConcatShearz(Shx, Shy);
}

void BaseObject::Reflect(bool x, bool y, bool z)
{
	transFMat.ConcatReflect(x, y, z);
}

void BaseObject::LoadIdentity()
{
	transFMat.loadIdentity();
}

Vector3f BaseObject::getNormal(Point3f p){
	return Vector3f(0,1,0);
}

