// UnitClass::UnitClass(UnitTypeClass *type, HouseClass *house) (0x006FA400)
// Default state for a type and owner: joins Units, takes the body facing for
// the turret, creates and links the type's locomotor, takes the type's turn
// rate, ammunition and strength, registers with the owner, becomes a veteran
// when the owner's type or training says so, and joins the techno index.
#include "shared/unit.hpp"
#include "shared/locomotion.hpp"
// @ref ??0FootClass@@QAE@PAVHouseClass@@@Z=004c2930
// @ref ??_7UnitClass@@6BIPersistStream@@@=007addf8
// @ref ??_7UnitClass@@6BIRTTITypeInfo@@@=007adddc
// @ref ??_7UnitClass@@6BINoticeSink@@@=007addd4
// @ref ??_7UnitClass@@6BINoticeSource@@@=007addcc
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Set_ROT@FacingClass@@QAEXH@Z=004b8e90
// @ref ?CreateInstance@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QAEJABUGUID@@PAUIUnknown@@K@Z=0041b650
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_4ea970@UnknownUnitHouse@@QAEXPAVUnitClass@@@Z=004ea970
// @ref ?Init@TechnoClass@@UAEXXZ=006c1c50
// @ref ?unknown_713520@UnknownTechnoPair@@QAEX_N@Z=00713520
// @ref ?unknown_6d83f0@TechnoClass@@QAEXH@Z=006d83f0
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58

UnitClass::UnitClass(UnitTypeClass *type, HouseClass *house) :
    FootClass(house),
    unknown_5a8(-1),
    Type(type),
    unknown_5b0(0),
    unknown_5b4(-1),
    unknown_5b8(false),
    unknown_5b9(false),
    unknown_5ba(false),
    unknown_5bb(false),
    unknown_5bc(-1),
    unknown_5c0(-1),
    unknown_5c4(0),
    unknown_5c8(false),
    unknown_5cc(0)
{
    Create_ID();
    Units.Add(this);
    unknown_2f8.Set_Current(unknown_2e0.Current());
    if (Type) {
        Locomotor = UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600>(Type->Locomotor);
        Locomotor.Checked()->Link_To_Object(this);
    }
    if (Type) {
        unknown_2e0.Set_ROT(Type->ROT);
        unknown_2f8.Set_ROT(Type->ROT);
        int ammo = Type->InitialAmmo;
        if (ammo != -1) {
            unknown_254 = ammo;
        } else {
            unknown_254 = Type->Ammo;
        }
        unknown_32a = Type->Cloakable;
        unknown_70 = Strength = Type->MaxStrength;
    }
    unknown_194 = CDTimerClass<FrameTimerClass>(0);
    if (House) {
        Unit_House_View(House)->unknown_4ea970(this);
    }
    TechnoClass::Init();
    if (Type) {
        if (House) {
            DynamicVectorClass<UnitTypeClass *> &veterans = Unit_House_View(House)->unknown_34->unknown_168;
            for (int index = 0; index < veterans.Count(); index++) {
                if (veterans[index] == Type) {
                    unknown_118.unknown_713520(true);
                    break;
                }
            }
        }
        if (House && Unit_House_View(House)->unknown_207 && !Type->Naval && Type->Trainable) {
            unknown_118.unknown_713520(true);
        }
        if (Type->Gunner) {
            unknown_6d83f0(0);
        }
    }
    unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
}
