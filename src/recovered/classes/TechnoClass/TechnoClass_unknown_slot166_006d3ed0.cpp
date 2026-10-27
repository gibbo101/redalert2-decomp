// int TechnoClass::unknown_slot166() (0x006D3ED0, slot 166)
// The pips to draw: the type's slot 29 count scaled by ammunition (PipScale
// 1) or passengers (PipScale 3) over the type's maximum, rounded, at least
// one while any remain.
#include "shared/techno.hpp"

int TechnoClass::unknown_slot166()
{
    double amount;
    double maximum;
    switch (unknown_slot32()->PipScale) {
    case 1:
        amount = unknown_254;
        maximum = unknown_slot32()->Ammo;
        break;
    case 3:
        amount = Cargo.Count;
        maximum = unknown_slot32()->Passengers;
        break;
    default:
        return 0;
    }
    int pips = (int)(unknown_slot32()->unknown_slot29() * (amount / maximum) + 0.5);
    if (pips == 0 && amount > 0.0) {
        pips = 1;
    }
    return pips;
}
