// Header-static dynamic initializers of the unit at 0x0063ED70 and its
// list globals (OwnerTalkClass_ConnectionListStruct); the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

// The unit's OwnerTalkClass object (0x00AB6D18; 0x20 bytes from its
// initializer 0x0063EF60 and atexit destructor 0x0063EFB0). The list of
// connections is its first member (vtable 0x007A8FEC is
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>); the
// destructor deletes every connection. Names and the two trailing fields
// are hypotheses.
class OwnerTalkClass {
public:
    struct ConnectionListStruct {
        int unknown_00;
    };

    OwnerTalkClass() : unknown_18(false), unknown_1c(0) {}
    ~OwnerTalkClass()
    {
        while (Connections.Count()) {
            delete Connections[0];
            Connections.Delete(0);
        }
    }

    DynamicVectorClass<ConnectionListStruct *> Connections;   // +0x00
    bool unknown_18;                                          // +0x18
    int unknown_1c;                                           // +0x1C
};

OwnerTalkClass unknown_OwnerTalkClass_00ab6d18;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UBE_NABV0@@Z=0063ff70
// @ref ??_7?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@6B@=007a8fec
// @ref ??_7?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@6B@=007a900c
// @ref ??_G?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEPAXI@Z=00640220
// @ref ??_G?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEPAXI@Z=006401d0
// @ref ?Clear@?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEXXZ=0063ff10
// @ref ?Clear@?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEXXZ=00640060
// @ref ?Fetch@?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UBEPAUConnectionListStruct@OwnerTalkClass@@H@Z=0063ff60
// @ref ?ID@?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEHABQAUConnectionListStruct@OwnerTalkClass@@@Z=006401a0
// @ref ?ID@?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEHPBQAUConnectionListStruct@OwnerTalkClass@@@Z=0063ff40
// @ref ?ID@?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEHABQAUConnectionListStruct@OwnerTalkClass@@@Z=00640090
// @ref ?ID@?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAEHPBQAUConnectionListStruct@OwnerTalkClass@@@Z=006400d0
// @ref ?Resize@?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAE_NHPBQAUConnectionListStruct@OwnerTalkClass@@@Z=006400f0
// @ref ?Resize@?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@UAE_NHPBQAUConnectionListStruct@OwnerTalkClass@@@Z=0063ffb0
// @ref ?unknown_OwnerTalkClass_00ab6d18@@3VOwnerTalkClass@@A=00ab6d18
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E41=0063efb0
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
// @ref _unknown_geometry_angle45=00ab6d50
// @ref _unknown_geometry_angle60=00ab6cf8
// @ref _unknown_geometry_angle90=00ab68c8
// @ref _unknown_geometry_b=00ab6d68
// @ref _unknown_geometry_c=00ab6d58
// @ref _unknown_geometry_deg_to_rad=007a8fe0
// @ref _unknown_geometry_diagonal=00ab6ce8
// @ref _unknown_geometry_g=00ab6d70
// @ref _unknown_geometry_h=00ab6d00
// @ref _unknown_geometry_i=00ab6d48
// @ref _unknown_geometry_j=00ab6d60
// @ref _unknown_geometry_k=00ab68e0
// @ref _unknown_geometry_l=00ab6d38
// @ref _unknown_geometry_sixty=007a8fd8
// @ref _unknown_static_rect=00ab68d0
