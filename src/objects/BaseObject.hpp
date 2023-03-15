#ifndef _BASEOBJECT_
#define _BASEOBJECT_



#include "../util/Matrix4x4.hpp"
#include "../util/Ray.hpp"
#include "../util/Color.hpp"
#include <iostream>
#include <tuple>
class BaseObject
{
protected:
    Matrix4x4 transFMat;
    Color c;
    float specular = -1;;
    float reflectiveness=-1;
    std::tuple<int, float,Vector3f> NO_INTERSECT{ 0,INFINITY,Vector3f(0,0,0)};

public:
    BaseObject();
    void setSpecular(float specular);
    float getSpecular();
    float getReflectivness();
    void setReflectivness(float r);
    virtual std::tuple<int, float, Vector3f> Intersects(const Ray& ray) = 0;
    virtual void Translate(float tx, float ty, float tz) ;
    virtual void RotateX(float angle);
    virtual void RotateY(float angle);
    virtual void RotateZ(float angle);
    virtual void Scale(float factor);
    virtual void Scale(float x, float y, float z);
    virtual void Shearx(float Shy, float Shz);
    virtual void Sheary(float Shx, float Shz);
    virtual void Shearz(float Shx, float Shy);
    virtual void Reflect(bool x, bool y, bool z);
    virtual void LoadIdentity();
    virtual void ApplyTransformation()=0;
    virtual Color getColor();
    virtual Vector3f getNormal(const Point3f p);
    virtual void ApplyCamera(const Matrix4x4 m)=0;
};

#endif // !1