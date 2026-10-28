// bool MultiplayerGameMode::unknown_slot44(HouseClass *house, int *money) -- 0x005B8060
// Spends the house's start money on random start units: units (Rules BaseUnit excluded) while
// more than a third of the money is left, else infantry, of the types the house may own at its
// tech level; each is placed near BaseCenter (given up after 20 failed placements), made a
// veteran with InitialVeteran and given mission 5 or 11. False when no type is available.
// @ref ??_E?$VectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcfa0
// @ref ??_E?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcff0
// @ref ??_E?$VectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd0e0
// @ref ??_E?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd130
// @ref ??_G?$VectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcfa0
// @ref ??8?$VectorClass@PAVUnitTypeClass@@@@UBE_NABV0@@Z=004da430
// @ref ?Fetch@?$VectorClass@PAVUnitTypeClass@@@@UBEPAVUnitTypeClass@@H@Z=004d55a0
// @ref ?Resize@?$VectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004da470
// @ref ?Clear@?$VectorClass@PAVUnitTypeClass@@@@UAEXXZ=004da520
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004da550
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004da590
// @ref ??_7?$DynamicVectorClass@PAVUnitTypeClass@@@@6B@=007a27e4
// @ref ??_G?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcff0
// @ref ?Resize@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004da5b0
// @ref ?Clear@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEXXZ=004d5550
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004da660
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004d5580
// @ref ??_G?$VectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd0e0
// @ref ??8?$VectorClass@PAVInfantryTypeClass@@@@UBE_NABV0@@Z=004da8f0
// @ref ?Fetch@?$VectorClass@PAVInfantryTypeClass@@@@UBEPAVInfantryTypeClass@@H@Z=004d5660
// @ref ?Resize@?$VectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004da930
// @ref ?Clear@?$VectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004da9e0
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004daa10
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004daa50
// @ref ??_7?$DynamicVectorClass@PAVInfantryTypeClass@@@@6B@=007a2864
// @ref ??_G?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd130
// @ref ?Resize@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004daa70
// @ref ?Clear@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004d5610
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004dab20
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004d5640
// @ref ??_7?$VectorClass@PAVInfantryTypeClass@@@@6B@=007a2884
// @ref ??_7?$VectorClass@PAVUnitTypeClass@@@@6B@=007a2804
// @ref ??0?$VectorClass@PAVInfantryTypeClass@@@@QAE@IPBQAVInfantryTypeClass@@@Z=005b9890
// @ref ??0?$VectorClass@PAVUnitTypeClass@@@@QAE@IPBQAVUnitTypeClass@@@Z=005b9840
// @ref ?Unknown_004EF6F0@HouseClass@@QAEPAVUnitTypeClass@@ABV?$TypeList@PAVUnitTypeClass@@@@@Z=004ef6f0
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVObjectClass@@@8=007ce548
// @ref ??_R0?AVTechnoClass@@@8=007ce5a8
// @ref ?Unknown_00660b60@@YIHPAVObjectClass@@AAVCell@@H@Z=00660b60
#include "shared/techno.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/special.hpp"
#include "shared/multiplayer_game_mode.hpp"

bool MultiplayerGameMode::unknown_slot44(HouseClass *house, int *money)
{
    if (*money > 0) {
        int start = *money;
        DynamicVectorClass<UnitTypeClass *> unit_list;
        DynamicVectorClass<InfantryTypeClass *> infantry_list;
        int owner = 1 << house->Type->ArrayIndex;
        for (int u = 0; u < UnitTypes.Count(); u++) {
            UnitTypeClass *unit_type = UnitTypes[u];
            if (unit_type->AllowedToStartInMultiplayer && (unit_type->Owner & owner)
                && unit_type->TechLevel <= house->unknown_11c && !Rules->BaseUnit.Is_Present(unit_type)) {
                unit_list.Add(unit_type);
            }
        }
        for (int i = 0; i < InfantryTypes.Count(); i++) {
            InfantryTypeClass *infantry_type = InfantryTypes[i];
            if (infantry_type->AllowedToStartInMultiplayer && (infantry_type->Owner & owner)
                && infantry_type->TechLevel <= house->unknown_11c) {
                infantry_list.Add(infantry_type);
            }
        }
        if (unit_list.Count() == 0 && infantry_list.Count() == 0) {
            return false;
        }
        int tries = 20;
        while (*money > 0 && tries > 0) {
            TechnoTypeClass *type;
            if (*money > start / 3 && unit_list.Count() != 0) {
                type = unit_list[unknown_id_source_a3d290->Random()(0, unit_list.Count() - 1)];
            } else {
                type = infantry_list[unknown_id_source_a3d290->Random()(0, infantry_list.Count() - 1)];
            }
            ObjectClass *object = type->unknown_slot35(house);
            TechnoClass *techno = dynamic_cast<TechnoClass *>(object);
            Cell cell = Cell(house->BaseCenter.X / 256, house->BaseCenter.Y / 256);
            if (!Unknown_00660b60(techno, cell, 4)) {
                delete techno;
                tries--;
            } else {
                *money -= type->Raw_Cost();
                if (unknown_id_source_a3d290->Special().InitialVeteran) {
                    techno->unknown_118.Unknown_00713550(true);
                }
                if (house->unknown_func_4f52f0()) {
                    techno->unknown_slot118(5);
                } else {
                    techno->unknown_slot118(11);
                }
            }
        }
    }
    return true;
}
