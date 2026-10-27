// ??0ParasiteClass@@QAE@PAVAbstractClass@@@Z (0x00606240)
// Parasite of owner, detached; listed in the unit list.
#include "shared/parasite.hpp"

ParasiteClass::ParasiteClass(AbstractClass *owner)
{
    Owner = owner;
    unknown_28 = 0;
    unknown_38 = CDTimerClass<FrameTimerClass>();
    unknown_2c = CDTimerClass<FrameTimerClass>();
    unknown_54 = false;
    unknown_4c = 0;
    unknown_50 = 0;
    Victim = 0;
    unknown_48 = 0;
    unknown_ParasiteClass_list_00a76430.Add(this);
}
