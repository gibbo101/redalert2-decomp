// UnknownBeacon::Unknown_0042E080 (0x0042E080): the beacon is placed by a house that is the player's
// ally both ways and not defeated (+0x13D).
#include "shared/beacon.hpp"
#include "shared/house.hpp"

bool UnknownBeacon::Unknown_0042E080()
{
    if ((unknown_flags & 1) && unknown_player_a35db4->Is_Ally(unknown_house)
        && Houses[unknown_house]->Is_Ally(unknown_player_a35db4) && !Houses[unknown_house]->unknown_13d) {
        return true;
    }
    return false;
}
