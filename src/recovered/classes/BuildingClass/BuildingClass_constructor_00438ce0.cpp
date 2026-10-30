// BuildingClass::BuildingClass(BuildingTypeClass *type, HouseClass *house) (0x00438CE0)
// Default state for a type and owner; faces the type's initial direction,
// joins Buildings, the lists at 0x00AC0C80/0x00AC0BF8 and the techno index,
// and sizes the radio links from the type (at least one).
#include "shared/building.hpp"
#include "shared/unknown_static_rect.hpp"
// @ref ??0TechnoClass@@QAE@PAVHouseClass@@@Z=006c0cd0
// @ref ??_7BuildingClass@@6BIPersistStream@@@=0079cbbc
// @ref ??_7BuildingClass@@6BIRTTITypeInfo@@@=0079cba0
// @ref ??_7BuildingClass@@6BINoticeSink@@@=0079cb98
// @ref ??_7BuildingClass@@6BINoticeSource@@@=0079cb90
// @ref ??_7?$DynamicVectorClass@PAVInfantryClass@@@@6B@=0079d054
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Init@BuildingClass@@UAEXXZ=0043f840
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30
// @ref ?Set_Radio_Count@RadioClass@@QAEXH@Z=00636f40
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?unknown_abstracts_ac0c80@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c80
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref _unknown_static_rect=0084ed00
// @ref _unknown_geometry_l=0084ed30

BuildingClass::BuildingClass(BuildingTypeClass *type, HouseClass *house) :
    TechnoClass(house),
    Type(type),
    unknown_41c(0),
    unknown_42c(-1),
    unknown_430(-1),
    unknown_434(0),
    unknown_438(0),
    unknown_43c(0),
    unknown_440(0),
    unknown_444(0),
    unknown_4bc(false),
    unknown_4cc(-1),
    unknown_4d0(-1),
    unknown_4d4(0),
    GateTimer(0),
    unknown_4e8(0),
    unknown_4ec(0),
    unknown_4f0(0),
    unknown_50c(unknown_static_rect),
    unknown_51c(unknown_geometry_l),
    unknown_528(Point2D(0, 0)),
    unknown_530(true),
    unknown_531(false),
    unknown_534(0),
    unknown_538(false),
    unknown_539(false),
    unknown_56c(0),
    unknown_598(false),
    unknown_599(false),
    unknown_59a(false),
    unknown_59b(false),
    unknown_59c(false),
    unknown_5ac(true),
    unknown_5ad(false),
    unknown_5ae(false),
    unknown_5af(false),
    unknown_5b0(false),
    unknown_5b1(false),
    unknown_5b2(false),
    unknown_5b3(false),
    unknown_5b4(false),
    unknown_5b5(false),
    unknown_5b6(false),
    unknown_5b7(false),
    unknown_5b8(false),
    unknown_5b9(false),
    unknown_5ba(true),
    unknown_5bb(0),
    unknown_5bc(0),
    unknown_5bd(false),
    unknown_5c0(0),
    unknown_5c4(1000),
    unknown_5c6(false),
    unknown_5c7(-1),
    unknown_5c8(0),
    unknown_5d8(0)
{
    Create_ID();
    for (int i = 0; i < 3; i++) {
        unknown_4c0[i] = 0;
    }
    unknown_5cc = CoordStruct(0, 0, 0);
    if (Type) {
        unknown_2c8.Set_Desired(UnknownFacingDir(Type->BarrelStartPitch << 8));
    }
    memset(unknown_454, 0, sizeof(unknown_454));
    for (int index = 0; index < 8; index++) {
        unknown_49c[index] = 0;
    }
    unknown_570.Init();
    unknown_584.Init();
    unknown_2c8.Set_Desired(UnknownFacingDir(0x4000));
    unknown_4f4.Value = 0;
    unknown_BuildingClass_list_00a40af8.Add(this);
    Init();
    unknown_abstracts_ac0c80.Add(this);
    unknown_abstracts_ac0bf8.Add(this);
    unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
    if (Type) {
        int count = Type->NumberOfDocks;
        if (count < 1) {
            count = 1;
        }
        Set_Radio_Count(count);
    } else {
        Set_Radio_Count(1);
    }
}
