#ifndef _BASEOBJECT_
#define _BASEOBJECT_



#include "../util/Matrix4x4.hpp"
#include "../util/Ray.hpp"
#include "../util/Color.hpp"
#include <iostream>
class BaseObject
{
protected:
    Matrix4x4 transFMat;
    Color c;
    float t_min=-INFINITY;
public:

    virtual int Intersects(Ray& ray) = 0;
    void Translate(float tx, float ty, float tz) ;
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    float getTmin();
    virtual void ApplyTransformation()=0;
    Color getColor();
};

#endif // !1