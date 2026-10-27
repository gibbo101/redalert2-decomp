// int TechnoTypeClass::unknown_slot29() const (0x006DE220)
// Pip count for PipScale= (hypothesis: RA1 Max_Pips); the jump table follows
// the code (0x006DE250, 4 entries).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

int TechnoTypeClass::unknown_slot29() const
{
    switch (PipScale) {
    case 4:
        return 10;
    case 1:
        return Ammo;
    case 2:
        return 5;
    case 3:
        return Passengers;
    }
    return 0;
}
