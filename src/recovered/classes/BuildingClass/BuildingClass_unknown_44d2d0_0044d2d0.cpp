// void BuildingClass::unknown_44d2d0(int layer) (0x0044D2D0)
// Gives every animation in unknown_454 the layer; 0xF becomes 0x10 when
// slot 25 answers 5 (slot 79 expands it after each animation).
#include "shared/building.hpp"

void BuildingClass::unknown_44d2d0(int layer)
{
    int value = layer;
    if (layer == 0xF && unknown_slot25(false, 0) == 5) {
        value = 0x10;
    }
    for (int anim = 0; anim < 18; anim++) {
        if (unknown_454[anim] != 0) {
            ((UnknownBuildingAnim *)unknown_454[anim])->unknown_158 = value;
        }
    }
}
