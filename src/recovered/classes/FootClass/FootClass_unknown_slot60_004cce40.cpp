// void FootClass::unknown_slot60() (0x004CCE40)
// The unit is removed: the owned object at +0x230 is told (0x004681E0),
// the unit leaves its team, then ObjectClass's slot 60.
#include "shared/foot.hpp"
// @ref ?Unknown_004681E0@UnknownTechno230@@QAEXXZ=004681e0
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_slot60@ObjectClass@@UAEXXZ=005d4e90

void FootClass::unknown_slot60()
{
    if (unknown_230 != 0) {
        ((UnknownTechno230 *)unknown_230)->Unknown_004681E0();
    }
    if (Team != 0) {
        Team->Unknown_006B8FB0(this, -1, 0);
    }
    TechnoClass::unknown_slot60();
}
