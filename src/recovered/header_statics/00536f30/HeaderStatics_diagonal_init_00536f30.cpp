// Header-static dynamic initializers of the unit at 0x00536F30 and its
// list globals (LightSourceClass, LightSourceClass_PendingCellClass); the other drafts of this plan are emitted by this file.
// A list whose atexit thunk tests and sets a guard bit is a static data
// member (VC6 guards their destruction); its owner class is a hypothesis.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

#include "shared/light_source.hpp"

class LightSourceClass::PendingCellClass {
public:
    static DynamicVectorClass<PendingCellClass *> Array;   // 0x00A6E848
};

// The unit's list of LightSourceClass (0x00A6E818; name is a hypothesis).
DynamicVectorClass<LightSourceClass *> unknown_LightSourceClass_list_00a6e818;
DynamicVectorClass<LightSourceClass::PendingCellClass *> LightSourceClass::PendingCellClass::Array;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVLightSourceClass@@@@UBE_NABV0@@Z=00537da0
// @ref ??8?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UBE_NABV0@@Z=00538000
// @ref ??_7?$DynamicVectorClass@PAVLightSourceClass@@@@6B@=007a54b4
// @ref ??_7?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@6B@=007a54f4
// @ref ??_7?$VectorClass@PAVLightSourceClass@@@@6B@=007a54d4
// @ref ??_7?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@6B@=007a5514
// @ref ??_G?$DynamicVectorClass@PAVLightSourceClass@@@@UAEPAXI@Z=005382b0
// @ref ??_G?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEPAXI@Z=00538350
// @ref ??_G?$VectorClass@PAVLightSourceClass@@@@UAEPAXI@Z=00538260
// @ref ??_G?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEPAXI@Z=00538300
// @ref ?Array@PendingCellClass@LightSourceClass@@2V?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@A=00a6e848
// @ref ?Clear@?$DynamicVectorClass@PAVLightSourceClass@@@@UAEXXZ=00537ce0
// @ref ?Clear@?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEXXZ=00537d40
// @ref ?Clear@?$VectorClass@PAVLightSourceClass@@@@UAEXXZ=00537e90
// @ref ?Clear@?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEXXZ=005380f0
// @ref ?Fetch@?$VectorClass@PAVLightSourceClass@@@@UBEPAVLightSourceClass@@H@Z=00537d30
// @ref ?Fetch@?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UBEPAVPendingCellClass@LightSourceClass@@H@Z=00537d90
// @ref ?ID@?$DynamicVectorClass@PAVLightSourceClass@@@@UAEHABQAVLightSourceClass@@@Z=00537fd0
// @ref ?ID@?$DynamicVectorClass@PAVLightSourceClass@@@@UAEHPBQAVLightSourceClass@@@Z=00537d10
// @ref ?ID@?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEHABQAVPendingCellClass@LightSourceClass@@@Z=00538230
// @ref ?ID@?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEHPBQAVPendingCellClass@LightSourceClass@@@Z=00537d70
// @ref ?ID@?$VectorClass@PAVLightSourceClass@@@@UAEHABQAVLightSourceClass@@@Z=00537ec0
// @ref ?ID@?$VectorClass@PAVLightSourceClass@@@@UAEHPBQAVLightSourceClass@@@Z=00537f00
// @ref ?ID@?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEHABQAVPendingCellClass@LightSourceClass@@@Z=00538120
// @ref ?ID@?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UAEHPBQAVPendingCellClass@LightSourceClass@@@Z=00538160
// @ref ?Resize@?$DynamicVectorClass@PAVLightSourceClass@@@@UAE_NHPBQAVLightSourceClass@@@Z=00537f20
// @ref ?Resize@?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@UAE_NHPBQAVPendingCellClass@LightSourceClass@@@Z=00538180
// @ref ?Resize@?$VectorClass@PAVLightSourceClass@@@@UAE_NHPBQAVLightSourceClass@@@Z=00537de0
// @ref ?Resize@?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@UAE_NHPBQAVPendingCellClass@LightSourceClass@@@Z=00538040
// @ref ?unknown_LightSourceClass_list_00a6e818@@3V?$DynamicVectorClass@PAVLightSourceClass@@@@A=00a6e818
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E42=00537160
// @ref _$E47=005371e0
// @ref _$S48=00a6e7c8
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
// @ref _unknown_geometry_angle45=00a6e838
// @ref _unknown_geometry_angle60=00a6e7f8
// @ref _unknown_geometry_angle90=00a6e7d0
// @ref _unknown_geometry_b=00a6e868
// @ref _unknown_geometry_c=00a6e840
// @ref _unknown_geometry_deg_to_rad=007a54a8
// @ref _unknown_geometry_diagonal=00a6e7f0
// @ref _unknown_geometry_g=00a6e870
// @ref _unknown_geometry_h=00a6e800
// @ref _unknown_geometry_i=00a6e830
// @ref _unknown_geometry_j=00a6e860
// @ref _unknown_geometry_k=00a6e7e8
// @ref _unknown_geometry_l=00a6e808
// @ref _unknown_geometry_sixty=007a54a0
// @ref _unknown_static_rect=00a6e7d8
