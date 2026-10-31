// void RadarClass::Unknown_00633000(int mode, bool sound) (0x00633000)
// TibSun's Radar_Activate: switches the radar mode (+0x14AC); an observer in a
// multiplayer game always gets mode 1; a running movie keeps the request
// (+0x14B0); modes 1 and above queue the next movie (0x0062F150, expanded)
// when the radar is up, otherwise turn it on or off (0x00632F30).
#include "shared/radar.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?Unknown_00632F30@RadarClass@@QAEX_N0@Z=00632f30
void RadarClass::Unknown_00633000(int mode, bool sound)
{
    if (unknown_game_mode_a3d298 && unknown_player_a35db4->unknown_13d && unknown_int_a3d548) {
        mode = 1;
    }
    if (unknown_14ac == mode) {
        return;
    }
    if ((unknown_14ac == 3 || (unknown_14ac == 4 && mode != 3)) && unknown_14a8 != 5) {
        unknown_14b0 = mode;
        return;
    }
    switch (mode) {
    case 0:
        Unknown_00632F30(false, unknown_14ac == 1);
        break;
    case 1:
        if ((unknown_14a8 == 1 || unknown_14a8 == 5) && unknown_14d4 == true) {
            Unknown_0062F150();
            break;
        }
        Unknown_00632F30(unknown_14d4, sound);
        break;
    case 4:
        break;
    default:
        if (unknown_14a8 == 1 || unknown_14a8 == 5) {
            Unknown_0062F150();
            break;
        }
        Unknown_00632F30(true, false);
        break;
    }
    unknown_14ac = mode;
}
