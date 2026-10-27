// void AnimTypeClass::unknown_func_426700() (0x00426700)
// Frees a demand-loaded image once played (FreeAfterPlaying).
#include "shared/anim_type.hpp"

void AnimTypeClass::unknown_func_426700()
{
    if (DemandLoad && unknown_a4 != 0 && FreeAfterPlaying) {
        Debug_Printf("Freeing loaded image for %s\n", (char const *)Name);
        operator delete(unknown_a4);
        unknown_a4 = 0;
        unknown_a8 = false;
    }
}
