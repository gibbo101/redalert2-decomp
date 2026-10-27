// void HouseClass::unknown_func_4f5880() (0x004F5880)
// The local player's house tells the map (0x00559F10) unless the +0x566A flag is set.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_00559F10@MapClass@@QAEXXZ=00559f10

void HouseClass::unknown_func_4f5880()
{
    if (this == unknown_player_a35db4 && !unknown_566a) {
        Map.Unknown_00559F10();
    }
}
