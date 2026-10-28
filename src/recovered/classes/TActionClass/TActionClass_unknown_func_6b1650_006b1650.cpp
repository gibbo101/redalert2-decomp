// bool TActionClass::unknown_func_6b1650(...) (0x006B1650)
// Sets the map's local size from +0x34..+0x40, refits the radar and the subzones, clears every cell's overlay, shows the buildings and announces the new terrain; always true.
#include "shared/taction.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/building_class.hpp"
#include "shared/vox_class.hpp"
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ??_C@_0BJ@MALN@EVA_NewTerrainDiscovered?$AA@=007f6be4

bool TActionClass::unknown_func_6b1650(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Map.MapLocalSize = *(Rect const *)&unknown_34;
    Map.Unknown_00631D40();
    Map.Unknown_0055A550();
    CellClass *walk = Map.Unknown_0055A490();
    while (walk != 0) {
        walk->Unknown_00472540(-1);
        walk = Map.Unknown_0055A490();
    }
    Map.Unknown_0054EBD0();
    Map.Unknown_00563D40();
    Map.Unknown_00634030();
    for (int index = unknown_BuildingClass_list_00a40af8.Count() - 1; index >= 0; index--) {
        unknown_BuildingClass_list_00a40af8[index]->unknown_slot267(true);
    }
    Speech_Play_Name("EVA_NewTerrainDiscovered", -1, -1);
    return true;
}
