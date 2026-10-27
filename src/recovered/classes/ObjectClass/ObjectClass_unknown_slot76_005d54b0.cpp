// bool ObjectClass::unknown_slot76() (0x005D54B0)
#include "shared/object_type.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

bool ObjectClass::unknown_slot76()
{
    if (unknown_slot49(unknown_player_a35db4) && unknown_slot51(true) == 0) {
        return false;
    }
    return Class_Of()->unknown_200;
}
