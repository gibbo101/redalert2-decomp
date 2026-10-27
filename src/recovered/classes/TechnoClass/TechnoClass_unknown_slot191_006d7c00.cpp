// bool TechnoClass::unknown_slot191() (0x006D7C00, slot 191)
// Cell test 0x0047C2E0 for the player at 0x00A35DB4.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

bool TechnoClass::unknown_slot191()
{
    if (unknown_player_a35db4) {
        return Map_Cell(Center_Coord())->unknown_47c2e0(unknown_player_a35db4->ArrayIndex);
    }
    return false;
}
