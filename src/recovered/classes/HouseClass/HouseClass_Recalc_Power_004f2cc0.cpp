// Recounts active buildings' power and drain (0x004F2CC0,393bytes).
#include "shared/building_class.hpp"
#include "shared/factory_class.hpp"
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);

void HouseClass::Recalc_Power_004f2cc0()
{
    bool was_low = Power_Fraction() < 1.0;
    unknown_5668 = false;
    Power = 0;
    Drain = 0;
    int count = Buildings.Count();
    for (int index = 0; index < count; ++index) {
        BuildingClass *building = Buildings[index];
        if (building && !building->unknown_76 && building->unknown_74) {
            if (!Is_Player_Control() || building->unknown_373 || unknown_game_mode_a3d298 != 0) {
                Power += building->unknown_449d40();
                Drain += building->unknown_449dd0();
            }
        }
    }
    if (unknown_1ec.Value() != 0) Power = 0;
    Building_Refresh_House_Buildings_0044fa40(this);
    FactoryClass::Update_Rates(this);
    if (was_low != (Power_Fraction() < 1.0)) Update_Present_Super_Weapons();
    unknown_5669 = true;
}
