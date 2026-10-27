// void InfantryClass::unknown_slot256() (0x00509330, slot 256)
// For PermaDisguise types: sets +0x170, records the house (+0x410) and the
// rules object for it (+0x40C; by the house's +0x130); otherwise clears
// +0x170.
#include "shared/infantry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void InfantryClass::unknown_slot256()
{
    if (Type->PermaDisguise) {
        unknown_170 = true;
        unknown_410 = House;
        if (House->unknown_130 == 0) {
            unknown_40c = Rules->unknown_b6c;
        } else {
            unknown_40c = Rules->unknown_b70;
        }
    } else {
        unknown_170 = false;
    }
}
