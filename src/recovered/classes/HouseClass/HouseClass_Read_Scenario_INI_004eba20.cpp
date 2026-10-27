// void __fastcall HouseClass::Read_Scenario_INI(CCINIClass &ini) (0x004EBA20)
// Makes a house for every [Houses] entry (its Country= type, the first type
// when unknown; the entry value becomes its INI name), reads each house's
// section and, outside multiplayer, assigns the scenario difficulty (the
// computer difficulty to houses that are neither human nor player
// controlled). Without [Houses], one house per house type is made and read.
// @ref ??0HouseClass@@QAE@PAVHouseTypeClass@@@Z=004e18c0
// @ref ?Assign_Handicap@HouseClass@@QAEHH@Z=004e2e40
// @ref ?Read_INI@HouseClass@@QAE_NAAVCCINIClass@@@Z=004ebbb0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_06DAOK@Houses?$AA@=007da83c
// @ref ??_C@_07FNCB@Country?$AA@=007da834
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

void __fastcall HouseClass::Read_Scenario_INI(CCINIClass &ini)
{
    int count = ini.Entry_Count("Houses");
    for (int index = 0; index < count; index++) {
        char name[20];
        ini.Get_String("Houses", ini.Get_Entry("Houses", index), "", name, sizeof(name));
        int type = ini.Get_HousesType(name, "Country", -1);
        if (type == -1) {
            type = 0;
        }
        HouseClass *house = new HouseClass(HouseTypes[type]);
        house->IniName = FixedString<21>(name);
    }

    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *house = Houses[i];
        house->Read_INI(ini);
        if (!unknown_game_mode_a3d298 && (house->unknown_134 || house->unknown_135)) {
            house->Assign_Handicap(unknown_id_source_a3d290->Difficulty);
        } else if (!unknown_game_mode_a3d298) {
            house->Assign_Handicap(unknown_id_source_a3d290->unknown_610);
        }
    }

    if (Houses.Count() == 0) {
        for (int type = 0; type < HouseTypes.Count(); type++) {
            HouseClass *house = new HouseClass(HouseTypes[type]);
            house->Read_INI(ini);
        }
    }
}
