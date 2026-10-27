// Header-static dynamic initializers of the unit at 0x0063B300 and its
// list globals (RadarEventClass); the other drafts of this plan are emitted by this file.
// A list whose atexit thunk tests and sets a guard bit is a static data
// member (VC6 guards their destruction); its owner class is a hypothesis.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

// Only the members this unit defines; the layout is not recovered here.
class RadarEventClass {
public:
    static DynamicVectorClass<RadarEventClass *> Array;   // 0x00AB67E8
};

DynamicVectorClass<RadarEventClass *> RadarEventClass::Array;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVRadarEventClass@@@@UBE_NABV0@@Z=0063c820
// @ref ??_7?$DynamicVectorClass@PAVRadarEventClass@@@@6B@=007a8e6c
// @ref ??_7?$VectorClass@PAVRadarEventClass@@@@6B@=007a8e8c
// @ref ??_G?$DynamicVectorClass@PAVRadarEventClass@@@@UAEPAXI@Z=0063cb10
// @ref ??_G?$VectorClass@PAVRadarEventClass@@@@UAEPAXI@Z=0063cac0
// @ref ?Array@RadarEventClass@@2V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ?Clear@?$DynamicVectorClass@PAVRadarEventClass@@@@UAEXXZ=0063c7c0
// @ref ?Clear@?$VectorClass@PAVRadarEventClass@@@@UAEXXZ=0063c910
// @ref ?Fetch@?$VectorClass@PAVRadarEventClass@@@@UBEPAVRadarEventClass@@H@Z=0063c810
// @ref ?ID@?$DynamicVectorClass@PAVRadarEventClass@@@@UAEHABQAVRadarEventClass@@@Z=0063ca90
// @ref ?ID@?$DynamicVectorClass@PAVRadarEventClass@@@@UAEHPBQAVRadarEventClass@@@Z=0063c7f0
// @ref ?ID@?$VectorClass@PAVRadarEventClass@@@@UAEHABQAVRadarEventClass@@@Z=0063c940
// @ref ?ID@?$VectorClass@PAVRadarEventClass@@@@UAEHPBQAVRadarEventClass@@@Z=0063c980
// @ref ?Resize@?$DynamicVectorClass@PAVRadarEventClass@@@@UAE_NHPBQAVRadarEventClass@@@Z=0063c9a0
// @ref ?Resize@?$VectorClass@PAVRadarEventClass@@@@UAE_NHPBQAVRadarEventClass@@@Z=0063c860
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E42=0063b530
// @ref _$S43=00ab6768
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
// @ref _unknown_geometry_angle45=00ab6808
// @ref _unknown_geometry_angle60=00ab67c0
// @ref _unknown_geometry_angle90=00ab6770
// @ref _unknown_geometry_b=00ab6820
// @ref _unknown_geometry_c=00ab6810
// @ref _unknown_geometry_deg_to_rad=007a8d48
// @ref _unknown_geometry_diagonal=00ab67b0
// @ref _unknown_geometry_g=00ab6828
// @ref _unknown_geometry_h=00ab67d0
// @ref _unknown_geometry_i=00ab6800
// @ref _unknown_geometry_j=00ab681c
// @ref _unknown_geometry_k=00ab67a8
// @ref _unknown_geometry_l=00ab67d8
// @ref _unknown_geometry_sixty=007a8d40
// @ref _unknown_static_rect=00ab6778
