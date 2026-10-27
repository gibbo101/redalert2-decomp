// void BuildingClass::unknown_44c920(int index, bool damaged, bool garrisoned, int arg4) (0x0044C920)
// Starts the animation of an Anims index with the type's name for the
// state (damaged first, else garrisoned, else normal), when it has one.
#include "shared/building.hpp"
// @ref ?unknown_44ca60@BuildingClass@@QAEXPBDH_N1H@Z=0044ca60

void BuildingClass::unknown_44c920(int index, bool damaged, bool garrisoned, int arg4)
{
    char const *name;
    if (damaged) {
        name = Type->Anims[index].Damaged.Buffer;
    } else if (garrisoned) {
        name = Type->Anims[index].Garrisoned.Buffer;
    } else {
        name = Type->Anims[index].Anim.Buffer;
    }
    if (name && *name) {
        unknown_44ca60(name, index, damaged, garrisoned, arg4);
    }
}
