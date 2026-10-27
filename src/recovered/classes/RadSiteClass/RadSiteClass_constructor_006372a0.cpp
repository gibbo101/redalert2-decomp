// ??0RadSiteClass@@QAE@XZ (0x006372A0)
// Clears the site and lists it in the unit list.
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7RadSiteClass@@6BINoticeSink@@@=007a8bac
// @ref ??_7RadSiteClass@@6BINoticeSource@@@=007a8ba4
// @ref ??_7RadSiteClass@@6BIPersistStream@@@=007a8bd0
// @ref ??_7RadSiteClass@@6BIRTTITypeInfo@@@=007a8bb4
// @ref ??_ERadSiteClass@@UAEPAXI@Z=00637f90
// @ref ??_GRadSiteClass@@UAEPAXI@Z=00637f90
// @ref ?AI@RadSiteClass@@UAEXXZ=006378c0
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@RadSiteClass@@UBEXAAVWWCRCEngine@@@Z=00637470
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?GetClassID@RadSiteClass@@UAGJPAUGUID@@@Z=00637530
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@RadSiteClass@@UBEHXZ=00637480
// @ref ?Load@RadSiteClass@@UAGJPAUIStream@@@Z=00637490
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@RadSiteClass@@UAGJPAUIStream@@H@Z=00637510
// @ref ?Size_Of@RadSiteClass@@UBEHXZ=00637460
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
#include "shared/radsite.hpp"

RadSiteClass::RadSiteClass() :
    LightSource(0),
    BaseCell(0, 0),
    Spread(0),
    SpreadInLeptons(0),
    RadLevel(0),
    unknown_50(0),
    unknown_54(0),
    unknown_64(0),
    unknown_68(0),
    RadDuration(0),
    RadTimeLeft(0)
{
    unknown_RadSiteClass_list_00ab6620.Add(this);
}
