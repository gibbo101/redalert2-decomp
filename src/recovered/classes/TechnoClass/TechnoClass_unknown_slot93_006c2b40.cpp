// void TechnoClass::unknown_slot93(int arg1) (0x006C2B40, slot 93)
#include "shared/techno.hpp"
#include "shared/tag.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/house.hpp"
// @ref ?unknown_47bb30@UnknownCellClass@@QAEXXZ=0047bb30

void TechnoClass::unknown_slot93(int arg1)
{
    if (arg1 == 2) {
        if (unknown_208 != 0 && unknown_208->unknown_28 != 0) {
            unknown_208->unknown_6e2500();
        }
        Cell cell = Coord_Cell(Center_Coord());
        unknown_slot238();
        if (unknown_34 != 0) {
            unknown_34->Spring(0x22, this, unknown_cell_ac0148, 0, 0);
        }
        if (!unknown_32d && Map.Unknown_0055A660(cell, true)) {
            unknown_32d = true;
        }
        if (!unknown_373 && (Map_Cell_At(cell)->unknown_12c & 0x10)) {
            unknown_slot96(unknown_player_a35db4);
        }
        Map_Cell_At(cell)->unknown_47bb30();
    }
}
