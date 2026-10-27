// InfantryClass::InfantryClass(InfantryTypeClass *type, HouseClass *house) (0x004FF640)
// Takes an ID, joins the infantry list, initializes from the type, creates
// the type's locomotor and links it, sets the body facing's rate (0x7F)
// and joins the techno index.
#include "shared/infantry.hpp"
// @ref ??0FootClass@@QAE@PAVHouseClass@@@Z=004c2930
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58
// @ref _unknown_uuid_IUnknown_7ce610=007ce610
// @ref _unknown_uuid_ILocomotion_7ce600=007ce600
// @ref __imp__CoCreateInstance@20=0079a5f0
// @ref __imp__OleRun@4=0079a5f4
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Set_ROT@FacingClass@@QAEXH@Z=004b8e90
// @ref ??_U@YAPAXI@Z=00782017
// @ref ?Init@InfantryClass@@UAEXXZ=004ff8b0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7InfantryClass@@6BIPersistStream@@@=007a3540
// @ref ??_7InfantryClass@@6BIRTTITypeInfo@@@=007a3524
// @ref ??_7InfantryClass@@6BINoticeSink@@@=007a351c
// @ref ??_7InfantryClass@@6BINoticeSource@@@=007a3514

InfantryClass::InfantryClass(InfantryTypeClass *type, HouseClass *house) :
    FootClass(house),
    Type(type),
    Sequence(-1),
    unknown_5bc(0),
    unknown_5c0(false),
    unknown_5c1(false),
    unknown_5c2(false),
    unknown_5c3(false),
    unknown_5c4(false),
    unknown_5c5(false),
    unknown_5c8(0),
    unknown_5cc(false),
    unknown_5d0(2)
{
    Create_ID();
    Infantry.Add(this);
    Init();
    if (Type != 0) {
        Locomotor.CreateInstance(Type->Locomotor, 0, CLSCTX_ALL);
        Locomotor.Checked()->Link_To_Object(this);
    }
    unknown_2e0.Set_ROT(0x7F);
    unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
}

// Inline base copies: bindings from the original InfantryClass vtable slots.
// @ref ?unknown_slot47@FootClass@@UAE_NXZ=0041b470
// @ref ?unknown_slot48@TechnoClass@@UAE_NXZ=0041b410
// @ref ?unknown_slot178@FootClass@@UAE?AVCell@@XZ=0041b550
// @ref ?unknown_slot179@FootClass@@UAEXVCell@@@Z=0041b560
// @ref ?unknown_slot201@TechnoClass@@UAE_NXZ=006d8e80
// @ref ?unknown_slot206@TechnoClass@@UAEHXZ=006d8e90
// @ref ?unknown_slot284@FootClass@@UAE_NXZ=0041b460
// @ref ?unknown_slot302@FootClass@@UAEXPBVCell@@_N@Z=0041b530
// @ref ?unknown_slot305@FootClass@@UAEXH@Z=0041b540
