// bool CellClass::unknown_47ba10(int house) const (0x0047BA10): with a player
// house and the house's bit set, true for the player's own house or when the
// player's per-house counter at +0x7C is not positive.
#include "shared/cell.hpp"
#include "shared/house.hpp"

bool CellClass::unknown_47ba10(int house) const
{
    if (unknown_player_a35db4 != 0 && Is_House_Bit(house)) {
        if (house == unknown_player_a35db4->ArrayIndex) {
            return true;
        }
        if (unknown_7c[unknown_player_a35db4->ArrayIndex] <= 0) {
            return true;
        }
    }
    return false;
}
