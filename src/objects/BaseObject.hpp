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
    float t_min=INFINITY;
    float specular = -1;;
public:
    void setSpecular(float specular);
    float getSpecular();
    virtual int Intersects(Ray& ray) = 0;
    virtual void Translate(float tx, float ty, float tz) ;
    virtual void RotateX(float angle);
    virtual void RotateY(float angle);
    virtual void RotateZ(float angle);
    virtual void LoadIdentity();
    virtual float getTmin();
    virtual void ApplyTransformation()=0;
    virtual Color getColor();
    virtual Vector3f getNormal(const Point3f p);
};

#endif // !1