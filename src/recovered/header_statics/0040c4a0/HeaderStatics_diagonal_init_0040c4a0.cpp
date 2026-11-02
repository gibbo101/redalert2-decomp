// Header-static dynamic initializers of the unit at 0x0040C4A0 and the
// unit's IsometricTileClass list; the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/logic.hpp"
// @ref ??_7LogicClass@@6B@=0079a8ec
// @ref ??_GLogicClass@@UAEPAXI@Z=0040cb10
// @ref ??8?$VectorClass@PAVObjectClass@@@@UBE_NABV0@@Z=0040cbc0
// @ref ?Resize@?$DynamicVectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cd40
// @ref ?Clear@?$DynamicVectorClass@PAVObjectClass@@@@UAEXXZ=0040cb60
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cdf0
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cb90
// @ref ?Fetch@?$VectorClass@PAVObjectClass@@@@UBEPAVObjectClass@@H@Z=0040cbb0
// @ref ?Submit@LogicClass@@UAE_NPAVObjectClass@@_N@Z=0053e330
// @ref ?unknown_slot8@LayerClass@@UAEXXZ=0040caf0
// @ref ?unknown_slot9@LayerClass@@UAEXXZ=0040cb00
// @ref ?Detach@LogicClass@@UAEXPBVAbstractClass@@_N@Z=0053e110
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c
// @ref ??_G?$VectorClass@PAVObjectClass@@@@UAEPAXI@Z=0040ce20
// @ref ?Resize@?$VectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cc00
// @ref ?Clear@?$VectorClass@PAVObjectClass@@@@UAEXXZ=0040ccb0
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cce0
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cd20
// @ref ?Logic@@3VLogicClass@@A=00832470

class IsometricTileClass;

// The unit's list of IsometricTileClass objects (0x00832448; name is a hypothesis).
DynamicVectorClass<IsometricTileClass *> unknown_IsometricTileClass_list_00832448;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVIsometricTileClass@@@@UBE_NABV0@@Z=0040c770
// @ref ??_7?$DynamicVectorClass@PAVIsometricTileClass@@@@6B@=0079a8ac
// @ref ??_7?$VectorClass@PAVIsometricTileClass@@@@6B@=0079a8cc
// @ref ??_G?$DynamicVectorClass@PAVIsometricTileClass@@@@UAEPAXI@Z=0040ca20
// @ref ??_G?$VectorClass@PAVIsometricTileClass@@@@UAEPAXI@Z=0040c9d0
// @ref ?Clear@?$DynamicVectorClass@PAVIsometricTileClass@@@@UAEXXZ=0040c710
// @ref ?Clear@?$VectorClass@PAVIsometricTileClass@@@@UAEXXZ=0040c860
// @ref ?Fetch@?$VectorClass@PAVIsometricTileClass@@@@UBEPAVIsometricTileClass@@H@Z=0040c760
// @ref ?ID@?$DynamicVectorClass@PAVIsometricTileClass@@@@UAEHABQAVIsometricTileClass@@@Z=0040c9a0
// @ref ?ID@?$DynamicVectorClass@PAVIsometricTileClass@@@@UAEHPBQAVIsometricTileClass@@@Z=0040c740
// @ref ?ID@?$VectorClass@PAVIsometricTileClass@@@@UAEHABQAVIsometricTileClass@@@Z=0040c890
// @ref ?ID@?$VectorClass@PAVIsometricTileClass@@@@UAEHPBQAVIsometricTileClass@@@Z=0040c8d0
// @ref ?Resize@?$DynamicVectorClass@PAVIsometricTileClass@@@@UAE_NHPBQAVIsometricTileClass@@@Z=0040c8f0
// @ref ?Resize@?$VectorClass@PAVIsometricTileClass@@@@UAE_NHPBQAVIsometricTileClass@@@Z=0040c7b0
// @ref ?unknown_IsometricTileClass_list_00832448@@3V?$DynamicVectorClass@PAVIsometricTileClass@@@@A=00832448
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E41=0040c6d0
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
// @ref _unknown_geometry_angle45=00832428
// @ref _unknown_geometry_angle60=00832400
// @ref _unknown_geometry_angle90=008323d8
// @ref _unknown_geometry_b=00832440
// @ref _unknown_geometry_c=00832430
// @ref _unknown_geometry_deg_to_rad=0079a8a0
// @ref _unknown_geometry_diagonal=008323f8
// @ref _unknown_geometry_g=00832460
// @ref _unknown_geometry_h=00832408
// @ref _unknown_geometry_i=00832420
// @ref _unknown_geometry_j=00832438
// @ref _unknown_geometry_k=008323f0
// @ref _unknown_geometry_l=00832410
// @ref _unknown_geometry_sixty=0079a898
// @ref _unknown_static_rect=008323e0

// The logic layer: every object that runs its AI each frame (0x00832470; Westwood's Logic). Its
// definition emits the initializer 0x0040CA70 and the atexit destructor 0x0040CAB0.
LogicClass Logic;
