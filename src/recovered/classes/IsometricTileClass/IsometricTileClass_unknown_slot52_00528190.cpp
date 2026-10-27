// bool IsometricTileClass::unknown_slot52() (0x00528190)
// Takes the tile off the map (only while the 0x00A40958 flag is set).
#include "shared/isometric_tile.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

bool IsometricTileClass::unknown_slot52()
{
    if (unknown_flag_a40958 && !unknown_76) {
        unknown_slot81();
        unknown_slot54(true);
        unknown_slot71(0);
        unknown_76 = true;
        unknown_75 = false;
        return true;
    }
    return false;
}
