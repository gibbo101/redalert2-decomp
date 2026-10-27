// void HouseClass::unknown_func_4f3320(HouseClass *house) (0x004F3320)
// Marks the house's country in +0x5414; when that house is the player's, every
// techno of this house reveals its sight around it and the map redraws.
#include "shared/techno.hpp"
#include "shared/map_view.hpp"

void HouseClass::unknown_func_4f3320(HouseClass *house)
{
    unknown_5414 |= 1 << house->Type->House;
    if (house == unknown_player_a35db4) {
        for (int index = 0; index < Technos.Count(); index++) {
            TechnoClass *techno = Technos[index];
            if (techno != 0 && !techno->unknown_76 && techno->House == this) {
                CoordStruct coord = techno->Coord;
                Map.Unknown_00549C50(coord, techno->unknown_slot32()->Sight, this, false, false, false, true, true);
            }
        }
        Map.Flag_To_Redraw(2);
    }
}
