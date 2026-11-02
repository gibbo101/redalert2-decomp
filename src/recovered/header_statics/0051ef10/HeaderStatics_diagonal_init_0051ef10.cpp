// Header-static dynamic initializers of the unit at 0x0051EF10:  the
// shared/unknown_geometry.hpp constants and unknown_static_rect.hpp
// (0x0051EF10-0x0051F0F6); the other
// drafts of this plan are emitted by these includes.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#define RA2_ION_STORM_LISTS
#include "shared/lightning_storm.hpp"

// Ion.cpp's file statics with dynamic initializers: the storm cell
// (0x0051F100) and the three storm lists (0x0051F110/0x0051F1B0/0x0051F250,
// each registering its guarded atexit destructor).
Cell StormCoords = unknown_geometry_k;
DynamicVectorClass<AnimClass *> IonStormClass::CloudsManifesting;
DynamicVectorClass<AnimClass *> IonStormClass::CloudsPresent;
DynamicVectorClass<AnimClass *> IonStormClass::BoltsPresent;
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
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
// @ref _unknown_geometry_angle45=00a518f8
// @ref _unknown_geometry_angle60=00a518b8
// @ref _unknown_geometry_angle90=00a51870
// @ref _unknown_geometry_b=00a51928
// @ref _unknown_geometry_c=00a51900
// @ref _unknown_geometry_deg_to_rad=007a4548
// @ref _unknown_geometry_diagonal=00a518b0
// @ref _unknown_geometry_g=00a51930
// @ref _unknown_geometry_h=00a518c0
// @ref _unknown_geometry_i=00a518f0
// @ref _unknown_geometry_j=00a51920
// @ref _unknown_geometry_k=00a518a8
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?CloudsManifesting@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908
// @ref ?CloudsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?BoltsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _atexit=0078298a
// @ref ??_7?$DynamicVectorClass@PAVAnimClass@@@@6B@=007a4554
// @ref ??_7?$VectorClass@PAVAnimClass@@@@6B@=007a4574
// @ref ??_E?$DynamicVectorClass@PAVAnimClass@@@@UAEPAXI@Z=00520f50
// @ref ??_E?$VectorClass@PAVAnimClass@@@@UAEPAXI@Z=00520f00
// @ref ??8?$VectorClass@PAVAnimClass@@@@UBE_NABV0@@Z=00520ca0
// @ref ?Resize@?$DynamicVectorClass@PAVAnimClass@@@@UAE_NHPBQAVAnimClass@@@Z=00520e20
// @ref ?Clear@?$DynamicVectorClass@PAVAnimClass@@@@UAEXXZ=00520c40
// @ref ?ID@?$DynamicVectorClass@PAVAnimClass@@@@UAEHABQAVAnimClass@@@Z=00520ed0
// @ref ?ID@?$DynamicVectorClass@PAVAnimClass@@@@UAEHPBQAVAnimClass@@@Z=00520c70
// @ref ?Fetch@?$VectorClass@PAVAnimClass@@@@UBEPAVAnimClass@@H@Z=00520c90
// @ref ?Resize@?$VectorClass@PAVAnimClass@@@@UAE_NHPBQAVAnimClass@@@Z=00520ce0
// @ref ?Clear@?$VectorClass@PAVAnimClass@@@@UAEXXZ=00520d90
// @ref ?ID@?$VectorClass@PAVAnimClass@@@@UAEHABQAVAnimClass@@@Z=00520dc0
// @ref ?ID@?$VectorClass@PAVAnimClass@@@@UAEHPBQAVAnimClass@@@Z=00520e00
// @ref _$E47=0051f150
// @ref _$E53=0051f1f0
// @ref _$E59=0051f290
// @ref _$S48=00a51869
// @ref _$S54=00a51868
// @ref _unknown_geometry_l=00a518e0
// @ref _unknown_geometry_sixty=007a4540
// @ref _unknown_static_rect=00a51898
