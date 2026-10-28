// bool MultiplayerGameMode::unknown_slot43(HouseClass *house, int *money) -- 0x005B7F90
// With bases on, puts the house's base unit (from Rules BaseUnit) at its BaseCenter, or near
// it; false when there is none or it cannot be placed.
// @ref ?Unknown_004EF6F0@HouseClass@@QAEPAVUnitTypeClass@@ABV?$TypeList@PAVUnitTypeClass@@@@@Z=004ef6f0
// @ref ?Unknown_00660b60@@YIHPAVObjectClass@@AAVCell@@H@Z=00660b60
#include "shared/techno.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/multiplayer_game_mode.hpp"

bool MultiplayerGameMode::unknown_slot43(HouseClass *house, int *money)
{
    if (!unknown_session_a3d298.unknown_bases_20) {
        return true;
    }
    UnitTypeClass *type = house->Unknown_004EF6F0(Rules->BaseUnit);
    if (type != 0) {
        TechnoClass *unit = (TechnoClass *)new UnitClass(type, house);
        if (unit != 0) {
            CoordStruct &center = house->BaseCenter;
            if (unit->unknown_slot53(&center, 0)) {
                return true;
            }
            Cell cell = Cell(center.X / 256, center.Y / 256);
            if (Unknown_00660b60(unit, cell, 1)) {
                return true;
            }
            delete unit;
        }
    }
    return false;
}
