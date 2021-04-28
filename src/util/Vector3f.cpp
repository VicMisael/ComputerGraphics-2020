#include "Vector3f.hpp"


// float Q_rsqrt( float number )
// {
// 	long i;
// 	float x2, y;
// 	const float threehalfs = 1.5F;

// 	x2 = number * 0.5F;
// 	y  = number;
// 	i  = * ( long * ) &y;                       // evil floating point bit level hacking
// 	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
// 	y  = * ( float * ) &i;
// 	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
// 	return y;
// }
Vector3f::Vector3f(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    //this->xyz.m128_u32[3] = 0;
}
Vector3f::Vector3f(float _vec[3])
{
    for (int i = 0; i < 3; i++)
    {
        vec[i] = _vec[i];
    }
    //this->xyz.m128_u32[3] = 0;
}
#ifdef _USESIMDINTRINSICS
Vector3f::Vector3f(__m128 _xyz)
{
    xyz = _xyz;
}
#endif
void Vector3f::normalize()
{
    //float length = this->length();
    //Using Inntrinsics for SIMD
    float sqrdlength=x * x + y * y + z * z;
#ifdef _USESIMDINTRINSICS
        const __m128 scalar = _mm_set1_ps(length);
        xyz = _mm_div_ps(xyz, scalar);
#else
        x *= inverseSquare(sqrdlength);
        y *= inverseSquare(sqrdlength);
        z *= inverseSquare(sqrdlength);
#endif
    
}
float Vector3f::length()
{
    return sqrt(x * x + y * y + z * z);
}