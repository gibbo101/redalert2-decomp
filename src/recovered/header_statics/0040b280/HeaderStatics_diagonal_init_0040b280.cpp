// Header-static dynamic initializers of the unit at 0x0040B280:  the
// shared/unknown_geometry.hpp constants (0x0040B280-0x0040B441); the other
// drafts of this plan are emitted by these includes; BombList's definition below emits
// its initializer 0x0040B450 and atexit destructor 0x0040B4D0.
#include "shared/unknown_geometry.hpp"
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define BOMB_LIST_DECLARE_LIFETIME
#include "shared/vector_class.hpp"
#include "shared/saveload_lists.hpp"
// @ref ?BombList@@3VBombListClass@@A=008322e0
// @ref ?Clear@BombListClass@@QAEXXZ=00436710
// @ref ??_7?$DynamicVectorClass@PAVBombClass@@@@6B@=0079a7bc
// @ref ??_E?$DynamicVectorClass@PAVBombClass@@@@UAEPAXI@Z=0040bb20
// @ref ??8?$VectorClass@PAVBombClass@@@@UBE_NABV0@@Z=0040b610
// @ref ?Resize@?$DynamicVectorClass@PAVBombClass@@@@UAE_NHPBQAVBombClass@@@Z=0040b790
// @ref ?Clear@?$DynamicVectorClass@PAVBombClass@@@@UAEXXZ=0040b550
// @ref ?ID@?$DynamicVectorClass@PAVBombClass@@@@UAEHABQAVBombClass@@@Z=0040b840
// @ref ?ID@?$DynamicVectorClass@PAVBombClass@@@@UAEHPBQAVBombClass@@@Z=0040b580
// @ref ?Fetch@?$VectorClass@PAVBombClass@@@@UBEPAVBombClass@@H@Z=0040b5a0
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_E?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b9f0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b5e0
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_E?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b8b0
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b9d0
// @ref ??_7?$VectorClass@PAVBombClass@@@@6B@=0079a7dc
// @ref ??_E?$VectorClass@PAVBombClass@@@@UAEPAXI@Z=0040bad0
// @ref ?Resize@?$VectorClass@PAVBombClass@@@@UAE_NHPBQAVBombClass@@@Z=0040b650
// @ref ?Clear@?$VectorClass@PAVBombClass@@@@UAEXXZ=0040b700
// @ref ?ID@?$VectorClass@PAVBombClass@@@@UAEHABQAVBombClass@@@Z=0040b730
// @ref ?ID@?$VectorClass@PAVBombClass@@@@UAEHPBQAVBombClass@@@Z=0040b770
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
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
// @ref _unknown_geometry_angle45=00832330
// @ref _unknown_geometry_angle60=008322d0
// @ref _unknown_geometry_angle90=008322b8
// @ref _unknown_geometry_b=00832348
// @ref _unknown_geometry_c=00832338
// @ref _unknown_geometry_deg_to_rad=0079a790
// @ref _unknown_geometry_diagonal=008322c8
// @ref _unknown_geometry_g=00832350
// @ref _unknown_geometry_h=008322d8
// @ref _unknown_geometry_i=00832328
// @ref _unknown_geometry_j=00832340
// @ref _unknown_geometry_k=008322c0
// @ref _unknown_geometry_l=00832318
// @ref _unknown_geometry_sixty=0079a788

// The planted bombs and the BombSight units (0x008322E0).
BombListClass BombList;
