// int FootClass::unknown_slot132() (0x004C48E0)
// A capture step: unless the type is StupidHunt, a unit able to act at its
// location (slot 209) that is infantry heads for its target: an Engineer
// without C4 or ability 14 moves to it in mission 8; with C4 or ability 14 a
// building target puts it in mission 17; a VehicleThief moves to its target
// in mission 8, any other infantry drops the move and calls slot 304 (as do
// non-infantry units). Otherwise a human-controlled... (0x004F52F0) unit in
// a single-player game (0x00A3D298 zero) heads for the player's base centre
// in mission 2. Returns the mission's rate in frames plus 0..2.
// TibSun Do_MISSION_HUNT shape (each branch tests the infantry pointer); the
// base-centre cell starts as unknown_geometry_k and is then assigned (the
// original's dead store of k into the cell's slot).
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

int FootClass::unknown_slot132()
{
    CoordStruct coord;
    if (!unknown_slot32()->StupidHunt && unknown_slot209(&(coord = Coord), 0)) {
        InfantryClass *infantry = Kind_Of() == 15 ? (InfantryClass *)this : 0;
        if (infantry != 0 && infantry->Type->Engineer && !infantry->Type->C4 && !infantry->unknown_6d7910(14)) {
            unknown_slot260(unknown_228, 1);
            unknown_slot116(8, false);
            if (unknown_slot122()) {
                unknown_slot117();
            }
        } else if (infantry != 0 && (infantry->Type->C4 || infantry->unknown_6d7910(14)) && unknown_228 != 0 && unknown_228->Kind_Of() == 6) {
            unknown_slot260(unknown_228, 1);
            unknown_slot116(17, false);
            if (unknown_slot122()) {
                unknown_slot117();
            }
        } else if (infantry != 0 && infantry->Type->VehicleThief) {
            unknown_slot260(unknown_228, 1);
            unknown_slot116(8, false);
            if (unknown_slot122()) {
                unknown_slot117();
            }
        } else if (infantry != 0) {
            unknown_slot260(0, 1);
            unknown_slot304();
        } else {
            unknown_slot304();
        }
    } else if (!House->Unknown_004F52F0() && unknown_game_mode_a3d298 == 0) {
        Cell cell = unknown_geometry_k;
        cell = Coord_Cell(unknown_player_a35db4->BaseCenter);
        if (cell != unknown_geometry_k) {
            unknown_slot260((AbstractClass *)&Map[cell], 1);
            unknown_slot116(2, true);
        }
    } else {
        unknown_slot258();
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
