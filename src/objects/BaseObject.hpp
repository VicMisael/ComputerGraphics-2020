#ifndef _BASEOBJECT_
#define _BASEOBJECT_



#include "../util/Matrix4x4.hpp"
#include "../util/Ray.hpp"
#include "../util/Color.hpp"
#include <iostream>
class BaseObject
{
public:
    Matrix4x4 transFMat;
    Color c;
    virtual int Intersects(Ray& ray) = 0;
    void Translate(float tx, float ty, float tz) ;
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    virtual void ApplyTransformation()=0;
    Color getColor();
};

#endif // !1