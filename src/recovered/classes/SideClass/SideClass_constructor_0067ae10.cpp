// SideClass::SideClass(char const *ini_name) (0x0067AE10)
// An empty side named ini_name; registers it in Sides.
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_7SideClass@@6BINoticeSink@@@=007ab24c
// @ref ??_7SideClass@@6BINoticeSource@@@=007ab244
// @ref ??_7SideClass@@6BIPersistStream@@@=007ab270
// @ref ??_7SideClass@@6BIRTTITypeInfo@@@=007ab254
// @ref ??_E?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_ESideClass@@UAEPAXI@Z=0067b1f0
// @ref ??_G?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_GSideClass@@UAEPAXI@Z=0067b1f0
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Compute_CRC@SideClass@@UBEXAAVWWCRCEngine@@@Z=0067afd0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?GetClassID@SideClass@@UAGJPAUGUID@@@Z=0067b000
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@SideClass@@UBEHXZ=0067b1e0
// @ref ?Load@SideClass@@UAGJPAUIStream@@@Z=0067b040
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Save@SideClass@@UAGJPAUIStream@@H@Z=0067b160
// @ref ?Sides@@3V?$DynamicVectorClass@PAVSideClass@@@@A=008661b0
// @ref ?Size_Of@SideClass@@UBEHXZ=0067b1d0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
// @ref ?unknown_slot24@AbstractTypeClass@@UAEXH@Z=004109a0
#include "shared/side.hpp"

SideClass::SideClass(char const *ini_name) :
    AbstractTypeClass(ini_name)
{
    Create_ID();
    Sides.Add(this);
}
