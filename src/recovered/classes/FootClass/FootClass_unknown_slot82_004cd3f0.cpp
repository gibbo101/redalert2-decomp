// void FootClass::unknown_slot82(int arg1) (0x004CD3F0)
// An Organic type takes damage equal to its strength from the rules
// warhead at +0xC74; otherwise the parasite riding this unit restarts its
// timer (50 frames) and is told so, the +0x58C timer restarts, and
// TechnoClass's slot 82 runs.
#include "shared/foot.hpp"
#include "shared/parasite.hpp"
#include "shared/techno_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot82@TechnoClass@@UAEXH@Z=006d86b0
// @ref ?Unknown_00607440@ParasiteClass@@QAEXXZ=00607440
// @ref ?Frame@@3HA=00a40d2c

void FootClass::unknown_slot82(int arg1)
{
    if (unknown_slot32()->Organic) {
        int damage = unknown_slot32()->MaxStrength;
        unknown_slot86(&damage, 0, Rules->unknown_c74, 0, false, 0);
        return;
    }
    if (unknown_580 != 0) {
        unknown_580->unknown_588->unknown_2c = CDTimerClass<FrameTimerClass>(50);
        unknown_580->unknown_588->Unknown_00607440();
    }
    unknown_58c = CDTimerClass<FrameTimerClass>(0);
    TechnoClass::unknown_slot82(arg1);
}
