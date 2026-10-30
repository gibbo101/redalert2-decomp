// Clear overlapping planned cells when a base building leaves (0x004F3F40).
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"

void HouseClass::unknown_func_4f3f40(BuildingClass *building)
{
    if (unknown_flag_a40d13) return;
    CoordStruct position=building->Position_Coord_004f3f40();
    Cell location=Coord_Cell(position);
    int count = unknown_55f0.Nodes.Count();
    for (int index = 0; index < count; ++index) {
        if (unknown_55f0.Nodes[index].Type == building->Type->ArrayIndex &&
            unknown_55f0.Nodes[index].Cell == location) {
            Cell cell = unknown_55f0.Nodes[index].Cell;
            for (int other = 0; other < unknown_55f0.Nodes.Count(); ++other) {
                if (index != other && unknown_55f0.Nodes[other].Cell == cell)
                    unknown_55f0.Nodes[other].Cell = unknown_cell_a40f10;
            }
            if (building->Type->IsBaseDefense && unknown_game_mode_a3d298 != 0) {
                unknown_55f0.Nodes[index].Type = -1;
                unknown_55f0.Nodes[index].Cell = unknown_cell_a40f10;
            }
            return;
        }
    }
}
