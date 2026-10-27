// Header-static dynamic initializers of the unit at 0x006351B0 and its
// list globals (RadBeam); the other drafts of this plan are emitted by this file.
// A list whose atexit thunk tests and sets a guard bit is a static data
// member (VC6 guards their destruction); its owner class is a hypothesis.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

// Only the members this unit defines; the layout is not recovered here.
class RadBeam {
public:
    static DynamicVectorClass<RadBeam *> Array;   // 0x00AB64E0
};

DynamicVectorClass<RadBeam *> RadBeam::Array;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVRadBeam@@@@UBE_NABV0@@Z=00636340
// @ref ??_7?$DynamicVectorClass@PAVRadBeam@@@@6B@=007a885c
// @ref ??_7?$VectorClass@PAVRadBeam@@@@6B@=007a887c
// @ref ??_G?$DynamicVectorClass@PAVRadBeam@@@@UAEPAXI@Z=006365f0
// @ref ??_G?$VectorClass@PAVRadBeam@@@@UAEPAXI@Z=006365a0
// @ref ?Array@RadBeam@@2V?$DynamicVectorClass@PAVRadBeam@@@@A=00ab64e0
// @ref ?Clear@?$DynamicVectorClass@PAVRadBeam@@@@UAEXXZ=006362e0
// @ref ?Clear@?$VectorClass@PAVRadBeam@@@@UAEXXZ=00636430
// @ref ?Fetch@?$VectorClass@PAVRadBeam@@@@UBEPAVRadBeam@@H@Z=00636330
// @ref ?ID@?$DynamicVectorClass@PAVRadBeam@@@@UAEHABQAVRadBeam@@@Z=00636570
// @ref ?ID@?$DynamicVectorClass@PAVRadBeam@@@@UAEHPBQAVRadBeam@@@Z=00636310
// @ref ?ID@?$VectorClass@PAVRadBeam@@@@UAEHABQAVRadBeam@@@Z=00636460
// @ref ?ID@?$VectorClass@PAVRadBeam@@@@UAEHPBQAVRadBeam@@@Z=006364a0
// @ref ?Resize@?$DynamicVectorClass@PAVRadBeam@@@@UAE_NHPBQAVRadBeam@@@Z=006364c0
// @ref ?Resize@?$VectorClass@PAVRadBeam@@@@UAE_NHPBQAVRadBeam@@@Z=00636380
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E42=006353e0
// @ref _$S43=00ab6530
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
// @ref _unknown_geometry_angle45=00ab6510
// @ref _unknown_geometry_angle60=00ab64d0
// @ref _unknown_geometry_angle90=00ab64a8
// @ref _unknown_geometry_b=00ab6528
// @ref _unknown_geometry_c=00ab6518
// @ref _unknown_geometry_deg_to_rad=007a8850
// @ref _unknown_geometry_diagonal=00ab64c8
// @ref _unknown_geometry_g=00ab6534
// @ref _unknown_geometry_h=00ab64d8
// @ref _unknown_geometry_i=00ab6508
// @ref _unknown_geometry_j=00ab6520
// @ref _unknown_geometry_k=00ab64c0
// @ref _unknown_geometry_l=00ab64f8
// @ref _unknown_geometry_sixty=007a8848
// @ref _unknown_static_rect=00ab64b0
