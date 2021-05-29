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
#define _RENDERWITHSHADOWS_
#endif
//#ifndef _RENDERWITHREFLECTIONS_
//#define _RENDERWITHREFLECTIONS_
//#endif
#ifndef _SUPERSAMPLE_
//#define _SUPERSAMPLE_
#define SSRate 2
#endif

#ifndef _SUBSAMPLE_
//#define _SUBSAMPLE_
#define SubSSampleRate 2
#endif

#define inverseSquare(_x)  1/sqrt(_x);

#if defined(_SUBSAMPLE_) && defined (_SUPERSAMPLE_)
#error "it's not possible to subsample and supersample"
#endif
#define PI 3.14159265358979323846
#endif