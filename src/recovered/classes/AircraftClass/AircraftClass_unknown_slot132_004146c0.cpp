// int AircraftClass::unknown_slot132() (0x004146C0, slot 132)
// Out of ammunition: leave the team, slot 261 (0, 1) and wait the mission's
// delay (+0x10 minutes of 900 frames) plus 0-2 frames. Otherwise look for
// a target near the aircraft (with 0x40 first in some game modes); without
// one slot 261 (0, 1), with one queue mission 1. Returns the delay.
#include "shared/aircraft.hpp"
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref __ftol=0077f110
// @ref __real@8@4008e100000000000000=0079b608

int AircraftClass::unknown_slot132()
{
    if (unknown_254 == 0) {
        if (Team != 0) {
            Team->Unknown_006B8FB0(this, -1, 0);
        }
        unknown_slot261(0, 1);
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    if (unknown_228 == 0) {
        if (unknown_game_mode_a3d298 != 0) {
            CoordStruct coord = Coord;
            unknown_slot220(unknown_slot219(0x40, &coord, 0));
        }
        if (unknown_228 == 0) {
            CoordStruct coord = Coord;
            unknown_slot220(unknown_slot219(0, &coord, 0));
        }
        if (unknown_228 == 0) {
            unknown_slot261(0, 1);
            return 1;
        }
    }
    unknown_slot116(1, false);
    return 1;
}
