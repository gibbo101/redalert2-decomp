// The C runtime's fabs (inline fabs) and pow (an intrinsic at /O2: the compiler calls the x87
// helper _CIpow, 0x007821B0, with both operands on the FPU stack).
#ifndef RA2_SHARED_CRT_MATH_HPP
#define RA2_SHARED_CRT_MATH_HPP

extern "C" double __cdecl pow(double x, double y);
#pragma intrinsic(pow)
extern "C" double __cdecl fabs(double x);
#pragma intrinsic(fabs)

#endif
