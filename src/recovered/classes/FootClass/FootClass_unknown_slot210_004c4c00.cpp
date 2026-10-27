// void FootClass::unknown_slot210() (0x004C4C00)
// Slot 260 (0, 1), clears unknown_4d0, slot 291, then TechnoClass's.
#include "shared/foot.hpp"
// @ref ?unknown_slot210@TechnoClass@@UAEXXZ=006c9a90

void FootClass::unknown_slot210()
{
    unknown_slot260(0, 1);
    unknown_4d0 = -1;
    unknown_slot291();
    TechnoClass::unknown_slot210();
}
