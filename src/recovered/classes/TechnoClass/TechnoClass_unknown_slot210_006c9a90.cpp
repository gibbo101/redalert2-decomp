// void TechnoClass::unknown_slot210() (0x006C9A90, slot 210)
// Resets several states and the +0x238 object.
#include "shared/techno.hpp"
// @ref ?unknown_689b70@UnknownTechno238@@QAEXXZ=00689b70
// @ref ?unknown_68a4b0@UnknownTechno238@@QAEXXZ=0068a4b0

void TechnoClass::unknown_slot210()
{
    unknown_slot220(0);
    unknown_slot260(0, 1);
    unknown_slot152(3);
    if (unknown_238) {
        unknown_238->unknown_689b70();
        unknown_238->unknown_68a4b0();
    }
    unknown_slot54(1);
    unknown_slot81();
}
