// void TechnoClass::unknown_6cdc00(HouseClass *house) (0x006CDC00)
// Sets the owner; +0x372 is set exactly when it is the player's house.
#include "shared/techno.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

void TechnoClass::unknown_6cdc00(HouseClass *house)
{
    House = house;
    unknown_372 = house == unknown_player_a35db4 && unknown_player_a35db4 != 0;
}
