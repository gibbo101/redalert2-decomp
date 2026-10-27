// void TechnoClass::unknown_slot213(int cell) (0x006C5070, slot 213)
// Slot 212 with slot 174 of the same cell.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot213(AbstractClass *target)
{
    return unknown_slot212(target, unknown_slot174(target));
}
