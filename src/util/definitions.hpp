#ifndef _DEFINITIONSHEADER
#define _DEFINITIONSHEADER
#if defined _M_AMD64 || __x86_64__
#ifndef _USESIMDINTRINSICS
//#define _USESIMDINTRINSICS
#ifndef _USESSE4DOTPRODUCT
//#define _USESSE4DOTPRODUCT
#endif
#endif
#endif

#ifndef _RENDERWITHSHADOWS_
//#define _RENDERWITHSHADOWS_
#endif

#include <cmath>

template <typename T>
constexpr auto inverseSquare(T _x) { return 1 / std::sqrt(_x); }


#define GLM_FORCE_SWIZZLE

#if defined(_SUBSAMPLE_) && defined (_SUPERSAMPLE_)
#error "it's not possible to subsample and supersample"


#endif
#define PI 3.14159265358979323846
#endif
