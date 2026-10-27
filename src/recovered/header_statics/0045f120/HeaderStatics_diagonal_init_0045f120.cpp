// Select the actual full BuildingClass before shared/techno.hpp.
#define RA2_BUILDING_FULL
// Bullet.cpp: the unit's header-static dynamic initializers and
// BulletClass::Array (a static data member: its atexit thunk 0x0045F350
// tests and sets a guard bit, as VC6 does for class statics).
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/bullet.hpp"

DynamicVectorClass<BulletClass *> BulletClass::Array;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E42=0045f350
// @ref __CIpow=007821b0
// @ref __ftol=0077f110
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@40078000000000000000=0079a700
// @ref _atexit=0078298a
// @ref _unknown_geometry_angle45=00850328
// @ref _unknown_geometry_angle60=008502e8
// @ref _unknown_geometry_angle90=008502b8
// @ref _unknown_geometry_b=00850340
// @ref _unknown_geometry_c=00850330
// @ref _unknown_geometry_deg_to_rad=0079d2f8
// @ref _unknown_geometry_diagonal=008502e0
// @ref _unknown_geometry_g=00850348
// @ref _unknown_geometry_h=008502f0
// @ref _unknown_geometry_i=00850320
// @ref _unknown_geometry_j=00850338
// @ref _unknown_geometry_k=008502d8
// @ref _unknown_geometry_l=00850310
// @ref _unknown_geometry_sixty=0079d2f0
// @ref _unknown_static_rect=008502c8
