// void BuildingClass::unknown_44d0f0(int value, int frame) (0x0044D0F0)
// Gives each animation in unknown_454 the value and frame (when its type has
// +0x318 set) and then the building's layer (slot 79 expands it).
#include "shared/building.hpp"

void BuildingClass::unknown_44d0f0(int value, int frame)
{
    for (int index = 0; index < 18; index++) {
        AnimClass *anim = static_cast<AnimClass *>(unknown_454[index]);
        if (anim != 0) {
            if (anim->Class != 0 && anim->Class->ShouldUseCellDrawer) {
                anim->unknown_bc = value;
                anim->unknown_e4 = frame;
            }
            unknown_44d2d0(unknown_5bd);
        }
    }
}
