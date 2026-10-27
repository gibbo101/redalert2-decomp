// void BuildingClass::unknown_44d070(bool damaged) (0x0044D070)
// When the damaged state (unknown_5b6) changes, restarts every animation in
// unknown_454 with the type's name for the new state.
#include "shared/building.hpp"
// @ref ?unknown_44ca60@BuildingClass@@QAEXPBDH_N1H@Z=0044ca60

void BuildingClass::unknown_44d070(bool damaged)
{
    if (unknown_5b6 == damaged) {
        return;
    }
    unknown_5b6 = damaged;
    for (int index = 0; index < 18; index++) {
        if (unknown_454[index]) {
            char const *name;
            if (damaged) {
                name = Type->Anims[index].Damaged.Buffer;
            } else {
                name = Type->Anims[index].Anim.Buffer;
            }
            if (name && *name) {
                unknown_44ca60(name, index, damaged, 0, 0);
            }
        }
    }
}
