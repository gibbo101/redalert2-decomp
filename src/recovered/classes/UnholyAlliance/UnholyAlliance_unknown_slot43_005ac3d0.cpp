// bool UnholyAlliance::unknown_slot43(HouseClass *house, int *money) -- 0x005AC3D0
// Puts one unit of each of the first two Rules BaseUnit types near the house's BaseCenter:
// the first at the cell three cells down and right of it if it can be unlimboed there, else
// (and the second always) placed near the BaseCenter cell; false when any of them fails.
// @ref ?Unknown_00660b60@@YIHPAVObjectClass@@AAVCell@@H@Z=00660b60
#include "shared/techno.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/multiplayer_game_mode.hpp"

bool UnholyAlliance::unknown_slot43(HouseClass *house, int *money)
{
    bool failed = false;
    for (int i = 0; i < 2; i++) {
        UnitTypeClass *type = Rules->BaseUnit[i];
        if (type == 0) {
            failed = true;
            continue;
        }
        TechnoClass *unit = (TechnoClass *)new UnitClass(type, house);
        if (unit == 0) {
            failed = true;
            continue;
        }
        Cell cell = Coord_Cell(house->BaseCenter);
        Cell offset = cell + Cell(3, 3);
        if (i == 0 && unit->unknown_slot53(&CoordStruct(offset.X * 256 + 128, offset.Y * 256 + 128, 0), 0)) {
            continue;
        }
        Cell spot = Cell(house->BaseCenter.X / 256, house->BaseCenter.Y / 256);
        if (!Unknown_00660b60(unit, spot, 3)) {
            failed = true;
            delete unit;
        }
    }
    return !failed;
}
