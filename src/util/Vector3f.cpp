#include "Vector3f.hpp"
Vector3f::Vector3f()
{
    Vector3f(1, 1, 1);
}
Vector3f::Vector3f(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}
Vector3f::Vector3f(float _vec[3])
{
    for (int i = 0; i < 3; i++)
    {
        vec[i] = _vec[i];
    }
}
Vector3f::Vector3f(__m128 _xyz){
    xyz=_xyz;
}
void Vector3f::normalize(){
    float length=this->length();
    x*=1/length;
    y*=1/length;
    z*=1/length;
}
float Vector3f::length()
{
    return sqrt(x * x + y * y + z * z);
}