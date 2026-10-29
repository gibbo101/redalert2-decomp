// int Unknown535910::Unknown_00535B60() -- 0x00535B60
// The name width (-1 in a campaign).
#include "shared/unknown_globals.hpp"
// @ref ?unknown_screen_widths_7add68@@3PAHA=007add68

int Unknown535910::Unknown_00535B60()
{
    int width = -1;
    if (unknown_game_mode_a3d298 != 0) {
        width = unknown_8523e0 == unknown_screen_widths_7add68[0] ? 326 : 406;
    }
    return width;
}
