// ??0TemporalClass@@QAE@PAVAbstractClass@@@Z (0x006E1F80)
// Link for owner, listed in the unit list.
#include "shared/temporal.hpp"

TemporalClass::TemporalClass(AbstractClass *owner)
{
    Owner = owner;
    Target = 0;
    unknown_2c = CDTimerClass<FrameTimerClass>();
    unknown_40 = 0;
    unknown_44 = 0;
    unknown_TemporalClass_list_00ac02e0.Add(this);
    unknown_48 = 0;
    unknown_4c = 0;
    unknown_38 = 0;
    unknown_3c = 0;
}
