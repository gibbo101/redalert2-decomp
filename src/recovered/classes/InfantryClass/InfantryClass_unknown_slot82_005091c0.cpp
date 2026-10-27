// void InfantryClass::unknown_slot82(int arg1) (0x005091C0, slot 82)
// Kills the infantry: full-strength damage with the rules warhead (+0xC74),
// forced.
#include "shared/infantry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void InfantryClass::unknown_slot82(int arg1)
{
    int damage = Type->MaxStrength;
    unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
}
