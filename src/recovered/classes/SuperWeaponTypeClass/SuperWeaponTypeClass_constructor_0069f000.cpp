// SuperWeaponTypeClass::SuperWeaponTypeClass(char const *ini_name) (0x0069F000)
// Defaults (4500-frame recharge, powered); registers the type in
// SuperWeaponTypes; the sidebar image starts as the ID.
// @ref ??_7SuperWeaponTypeClass@@6BINoticeSink@@@=007ac294
// @ref ??_7SuperWeaponTypeClass@@6BINoticeSource@@@=007ac28c
// @ref ??_7SuperWeaponTypeClass@@6BIPersistStream@@@=007ac2b8
// @ref ??_7SuperWeaponTypeClass@@6BIRTTITypeInfo@@@=007ac29c
// @ref ??_ESuperWeaponTypeClass@@UAEPAXI@Z=0069f8c0
// @ref ??_GSuperWeaponTypeClass@@UAEPAXI@Z=0069f8c0
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@SuperWeaponTypeClass@@UBEXAAVWWCRCEngine@@@Z=0069f340
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?GetClassID@SuperWeaponTypeClass@@UAGJPAUGUID@@@Z=0069f1f0
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@SuperWeaponTypeClass@@UBEHXZ=0069f320
// @ref ?Load@SuperWeaponTypeClass@@UAGJPAUIStream@@@Z=0069f230
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Read_INI@SuperWeaponTypeClass@@UAE_NAAVCCINIClass@@@Z=0069f450
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@SuperWeaponTypeClass@@UAGJPAUIStream@@H@Z=0069f300
// @ref ?Size_Of@SuperWeaponTypeClass@@UBEHXZ=0069f330
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref _strncpy=007823d0
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?unknown_slot16@SuperWeaponTypeClass@@UBEHXZ=0069f440
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
// @ref ?unknown_slot24@AbstractTypeClass@@UAEXH@Z=004109a0
// @ref ?unknown_slot27@SuperWeaponTypeClass@@UBEHPBX0@Z=0069f8b0

SuperWeaponTypeClass::SuperWeaponTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    WeaponType(0),
    unknown_0xA0(-1),
    unknown_0xA4(-1),
    unknown_0xA8(-1),
    unknown_0xAC(-1),
    RechargeTime(4500),
    Type(-1),
    SidebarIcon(0),
    Action(0),
    AuxBuilding(0),
    UseChargeDrain(false),
    IsPowered(true),
    DisableableFromShell(false),
    PreClick(false),
    PostClick(false),
    PreDependent(-1),
    ShowTimer(false),
    ManualControl(false)
{
    Create_ID();
    ArrayIndex = SuperWeaponTypes.Count();
    SuperWeaponTypes.Add(this);
    SidebarImage = ID;
}
