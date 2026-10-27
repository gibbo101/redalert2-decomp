// Header-static dynamic initializers of the unit at 0x00684D50 and its
// list globals (UndoInfoStruct); the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

// 12 bytes, from DynamicVectorClass<UndoInfoStruct>::Resize (0x00687030,
// 0x007AB52C slot 2: new of count * 12, each element zeroed), operator==
// (0x00686FD0: three dword compares) and Fetch (0x00686FA0). Field names and
// types are hypotheses.
struct UndoInfoStruct {
    UndoInfoStruct() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    bool operator==(UndoInfoStruct const &other) const
    {
        return unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04 && unknown_08 == other.unknown_08;
    }
    bool operator!=(UndoInfoStruct const &other) const { return !(*this == other); }

    int unknown_00;     // +0x00
    int unknown_04;     // +0x04
    int unknown_08;     // +0x08
};

// The unit's list of UndoInfoStruct (0x00ABCE18; name is a hypothesis).
DynamicVectorClass<UndoInfoStruct> unknown_UndoInfoStruct_list_00abce18;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@UUndoInfoStruct@@@@UBE_NABV0@@Z=00686fd0
// @ref ??_7?$DynamicVectorClass@UUndoInfoStruct@@@@6B@=007ab50c
// @ref ??_7?$VectorClass@UUndoInfoStruct@@@@6B@=007ab52c
// @ref ??_G?$DynamicVectorClass@UUndoInfoStruct@@@@UAEPAXI@Z=00687380
// @ref ??_G?$VectorClass@UUndoInfoStruct@@@@UAEPAXI@Z=00687330
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ?Clear@?$DynamicVectorClass@UUndoInfoStruct@@@@UAEXXZ=00686f40
// @ref ?Clear@?$VectorClass@UUndoInfoStruct@@@@UAEXXZ=00687130
// @ref ?Fetch@?$VectorClass@UUndoInfoStruct@@@@UBE?AUUndoInfoStruct@@H@Z=00686fa0
// @ref ?ID@?$DynamicVectorClass@UUndoInfoStruct@@@@UAEHABUUndoInfoStruct@@@Z=006872f0
// @ref ?ID@?$DynamicVectorClass@UUndoInfoStruct@@@@UAEHPBUUndoInfoStruct@@@Z=00686f70
// @ref ?ID@?$VectorClass@UUndoInfoStruct@@@@UAEHABUUndoInfoStruct@@@Z=00687160
// @ref ?ID@?$VectorClass@UUndoInfoStruct@@@@UAEHPBUUndoInfoStruct@@@Z=006871b0
// @ref ?Resize@?$DynamicVectorClass@UUndoInfoStruct@@@@UAE_NHPBUUndoInfoStruct@@@Z=006871e0
// @ref ?Resize@?$VectorClass@UUndoInfoStruct@@@@UAE_NHPBUUndoInfoStruct@@@Z=00687030
// @ref ?unknown_UndoInfoStruct_list_00abce18@@3V?$DynamicVectorClass@UUndoInfoStruct@@@@A=00abce18
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E41=00684f80
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
// @ref _unknown_geometry_angle45=00abce78
// @ref _unknown_geometry_angle60=00abce50
// @ref _unknown_geometry_angle90=00abce10
// @ref _unknown_geometry_b=00abce90
// @ref _unknown_geometry_c=00abce80
// @ref _unknown_geometry_deg_to_rad=007ab500
// @ref _unknown_geometry_diagonal=00abce48
// @ref _unknown_geometry_g=00abce98
// @ref _unknown_geometry_h=00abce58
// @ref _unknown_geometry_i=00abce70
// @ref _unknown_geometry_j=00abce88
// @ref _unknown_geometry_k=00abce40
// @ref _unknown_geometry_l=00abce60
// @ref _unknown_geometry_sixty=007ab4f8
// @ref _unknown_static_rect=00abce30
