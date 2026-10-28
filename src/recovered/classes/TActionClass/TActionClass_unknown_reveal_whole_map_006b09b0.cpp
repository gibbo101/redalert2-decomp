// bool TActionClass::unknown_reveal_whole_map(...) (0x006B09B0)
// Once per player (house +0x188): walks every cell of the map, lets the radar mark each as seen for the player's house, and flags a full redraw; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?unknown_slot36@RadarClass@@UAE_NABVCell@@PAVHouseClass@@@Z=0062fc80
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0


bool TActionClass::unknown_reveal_whole_map(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (!unknown_player_a35db4->unknown_188) {
        unknown_player_a35db4->unknown_188 = true;
        Map.Unknown_0055A550();
        CellClass *cell;
        while ((cell = Map.Unknown_0055A490()) != 0) {
            Map.unknown_slot36(cell->MapCoords, unknown_player_a35db4);
        }
        Map.Flag_To_Redraw(1);
    }
    return true;
}
