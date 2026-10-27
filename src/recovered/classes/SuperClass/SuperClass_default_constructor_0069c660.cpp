// SuperClass::SuperClass() (0x0069C660)
// An unowned, untyped super; joins Supers.
// @ref ??_7SuperClass@@6BINoticeSink@@@=007ac1ec
// @ref ??_7SuperClass@@6BINoticeSource@@@=007ac1e4
// @ref ??_7SuperClass@@6BIPersistStream@@@=007ac210
// @ref ??_7SuperClass@@6BIRTTITypeInfo@@@=007ac1f4
// @ref ??_ESuperClass@@UAEPAXI@Z=0069ecd0
// @ref ??_GSuperClass@@UAEPAXI@Z=0069ecd0
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@SuperClass@@UBEXAAVWWCRCEngine@@@Z=0069eb20
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@SuperClass@@UAEXPAVAbstractClass@@_N@Z=0069eaf0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?GetClassID@SuperClass@@UAGJPAUGUID@@@Z=0069e9b0
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@SuperClass@@UBEHXZ=0069ecb0
// @ref ?Load@SuperClass@@UAGJPAUIStream@@@Z=0069e9f0
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@SuperClass@@UAGJPAUIStream@@H@Z=0069ead0
// @ref ?Size_Of@SuperClass@@UBEHXZ=0069ecc0
// @ref ?Supers@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35d28
// @ref ?What_Am_I@SuperClass@@UAGHXZ=0069eca0
// @ref ?unknown_cell_abd768@@3VCell@@B=00abd768
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
#include "shared/super.hpp"

SuperClass::SuperClass() :
    Type(0),
    House(0),
    unknown_0x48(true),
    unknown_0x4A(unknown_cell_abd768),
    Anim(0),
    AnimDetached(false),
    unknown_0x55(false),
    unknown_0x56(false),
    unknown_0x57(false),
    unknown_0x58(false),
    unknown_0x60(-1)
{
    unknown_0x38 = unknown_empty_wide_839d4c;
    Supers.Add(this);
}
