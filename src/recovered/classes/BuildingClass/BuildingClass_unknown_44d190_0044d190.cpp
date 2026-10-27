// void BuildingClass::unknown_44d190() (0x0044D190)
// Gives every animation in unknown_454 whose type has +0x318 set the slot
// 115 value and the frame (the height level of its cell, slot 254, adjusted
// by 0x006D86F0 when slot 203 holds; also kept in unknown_5c4), then the
// building's layer.
#include "shared/building.hpp"
// @ref ?unknown_6d86f0@TechnoClass@@QAEHH@Z=006d86f0

void BuildingClass::unknown_44d190()
{
    int value = unknown_slot115();
    int height = ((UnknownBuildingSlot105 *)unknown_slot105())->unknown_10a;
    int level = unknown_slot254(height);
    if (unknown_slot203()) {
        level = unknown_6d86f0(level);
    }
    unknown_5c4 = level;
    int frame = (unsigned short)level;
    for (int index = 0; index < 18; index++) {
        UnknownBuildingAnim *anim = (UnknownBuildingAnim *)unknown_454[index];
        if (anim != 0) {
            if (anim->Type != 0 && anim->Type->unknown_318) {
                anim->unknown_bc = value;
                anim->unknown_e4 = frame;
            }
            unknown_44d2d0(unknown_5bd);
        }
    }
    unknown_44d2d0(unknown_5bd);
}
