// int VeinholeMonsterClass::unknown_slot86(...) (0x007109C0, slot 86: take damage)
// ObjectClass's result decides the state (+0xB8): 4 -> 3 and the object is
// ended through 0x006ECB90, 5 -> unchanged, otherwise 2 and a 120 frame timer.
#include "shared/veinhole.hpp"
// @ref ?unknown_slot86@ObjectClass@@UAEHPAHHPAVWarheadTypeClass@@PAVTechnoClass@@_NH@Z=005d3d20
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

int VeinholeMonsterClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6)
{
    int result = ObjectClass::unknown_slot86(damage, distance, warhead, source, forced, arg6);
    switch (result) {
    case 0:
        break;
    case 4:
        unknown_b8 = 3;
        Unknown_006ECB90(this, false);
        break;
    case 5:
        return 5;
    default:
        unknown_b8 = 2;
        unknown_d4 = CDTimerClass<FrameTimerClass>(120);
        break;
    }
    return result;
}
