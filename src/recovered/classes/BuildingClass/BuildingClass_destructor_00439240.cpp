// BuildingClass::~BuildingClass() (0x00439240)
// Stops the audio controllers, releases the owned objects, leaves Buildings,
// the lists at 0x00AC0BF8/0x00AC0C80 and the techno index, updates the
// owner, and empties the two infantry lists.
#include "shared/building.hpp"
// @ref ??1TechnoClass@@UAE@XZ=006c20b0
// @ref ??_7BuildingClass@@6BIPersistStream@@@=0079cbbc
// @ref ??_7BuildingClass@@6BIRTTITypeInfo@@@=0079cba0
// @ref ??_7BuildingClass@@6BINoticeSink@@@=0079cb98
// @ref ??_7BuildingClass@@6BINoticeSource@@@=0079cb90
// @ref ??_7?$VectorClass@PAVInfantryClass@@@@6B@=0079d074
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ?unknown_537560@UnknownBuilding4E8@@QAEXH@Z=00537560
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_slot52@BuildingClass@@UAE_NXZ=00442060
// @ref ?unknown_44cfd0@BuildingClass@@QAEXH@Z=0044cfd0
// @ref ?Free_Buildup@BuildingTypeClass@@QAEXXZ=0045e920
// @ref ?unknown_slot234@BuildingClass@@UAEXH@Z=0044fb50
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?unknown_func_4f4b20@HouseClass@@QAEXXZ=004f4b20
// @ref ?unknown_4ea800@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea800
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Supers@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35d28
// @ref ?Delete@?$DynamicVectorClass@PAVBuildingClass@@@@QAE_NH@Z=00454b60
// @ref ?Delete@?$DynamicVectorClass@PAVAbstractClass@@@@QAE_NH@Z=00454b20
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Search_For_Node@?$UnknownIndexClass@JPAVObjectClass@@@@QAEPBUNodeElement@1@ABJ@Z=0041b990
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?unknown_abstracts_ac0c80@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0c80
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58

// Removes an object from one of the object lists (an inline wrapper).
static inline bool Remove_From(DynamicVectorClass<AbstractClass *> &list, AbstractClass *object)
{
    return list.Delete(object);
}

// Empties an infantry list but keeps its capacity (an inline helper).
static inline void Reset_List(DynamicVectorClass<InfantryClass *> &list)
{
    int size = list.Length();
    list.Clear();
    list.Resize(size);
}

BuildingClass::~BuildingClass()
{
    unknown_584.Unknown_00406070();
    unknown_570.Unknown_00406070();
    unknown_584.Unknown_00405C10();
    unknown_570.Unknown_00405C10();
    if (unknown_4e8) {
        unknown_4e8->unknown_537560(0);
        delete unknown_4e8;
        unknown_4e8 = 0;
    }
    Unknown_006ECB90(this, true);
    unknown_slot52();
    unknown_BuildingClass_list_00a40af8.Delete(this);
    unknown_44cfd0(-2);
    Type->Free_Buildup();
    unknown_4397c0();
    if (unknown_flag_a40958 && Type && Type->CloakGenerator) {
        unknown_5bb = -1;
        if (!unknown_5bc) {
            unknown_5bc = Type->CloakRadiusInCells;
        }
        unknown_75 = true;
        unknown_5bc = 1;
        unknown_slot234(1);
    }
    if (unknown_452800() != -1 || unknown_452860() != -1) {
        House->unknown_func_4f4b20();
    }
    if (unknown_flag_a40958) {
        if (Strength != unknown_43c) {
            House->unknown_5668 = true;
        }
        if (unknown_flag_a40958 && Type) {
            if (House) {
                House->unknown_4ea800(this);
            }
            unknown_slot52();
        }
    }
    delete unknown_41c;
    unknown_41c = 0;
    Remove_From(unknown_abstracts_ac0bf8, this);
    Remove_From(unknown_abstracts_ac0c80, this);
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    Type = 0;
    unknown_7d = false;
    Reset_List(unknown_53c);
    Reset_List(unknown_554);
}
