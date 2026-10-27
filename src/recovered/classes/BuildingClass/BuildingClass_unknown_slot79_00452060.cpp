// void BuildingClass::unknown_slot79(int arg1) (0x00452060)
// A non-zero argument sets unknown_75; then the techno's slot 79. The
// building's animations (unknown_454) take the slot 115 value and the
// slot 254 value for its cell's +0x10A (adjusted by 0x006D86F0 when slot
// 203 holds; also kept in unknown_5c4) when their type has +0x318 set, and
// all of them take the building's layer (unknown_5bd, 0x10 instead of 0xF
// when slot 25 answers 5) after each animation and once more at the end.
#include "shared/building.hpp"
// @ref ?unknown_slot79@TechnoClass@@UAEXH@Z=006c7440
// @ref ?unknown_6d86f0@TechnoClass@@QAEHH@Z=006d86f0

void BuildingClass::unknown_slot79(int arg1)
{
    if (arg1 != 0) {
        unknown_75 = true;
    }
    TechnoClass::unknown_slot79(arg1);
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
