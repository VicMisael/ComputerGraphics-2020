#ifndef _DEFINITIONSHEADER
#define _DEFINITIONSHEADER
#if defined _M_AMD64 || __x86_64__ 
#ifndef _USESIMDINTRINSICS
#define _USESIMDINTRINSICS
#ifndef _USESSE4DOTPRODUCT
//#define _USESSE4DOTPRODUCT
#endif
#endif
#endif

#ifndef _RENDERWITHSHADOWS_
#define _RENDERWITHSHADOWS_
#endif
#ifndef _RENDERWITHREFLECTIONS_
#define _RENDERWITHREFLECTIONS_
#endif
#ifndef _SUPERSAMPLE_
//#define _SUPERSAMPLE_
#define SSRate 2
#endif

#define PI 3.14159265358979323846
#endif