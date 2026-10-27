// void MapClass::unknown_slot27() (0x0054E300, slot 27)
// Outside the campaign and with the 0x00A3D2C1 option on, every +0x154
// entry that has a cell and whose countdown ran out is removed (0x00493930)
// and a new one placed (0x0054E410).
#include "shared/map.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3d2c1@@3_NA=00a3d2c1
// @ref ?unknown_cell_a6f238@@3VCell@@A=00a6f238
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_00493930@UnknownMapEntry154@@QAE_NXZ=00493930
// @ref ?Unknown_0054E410@MapClass@@QAE_NXZ=0054e410

void MapClass::unknown_slot27()
{
    if (unknown_game_mode_a3d298 != 0 && unknown_flag_a3d2c1) {
        for (int index = 0; index < 256; index++) {
            if (unknown_154[index].Cell != unknown_cell_a6f238 && unknown_154[index].Timer.Value() == 0) {
                unknown_154[index].Unknown_00493930();
                Unknown_0054E410();
            }
        }
    }
}
