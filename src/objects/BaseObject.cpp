#include "BaseObject.hpp"

Color BaseObject::getColor(){
    return c;
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
