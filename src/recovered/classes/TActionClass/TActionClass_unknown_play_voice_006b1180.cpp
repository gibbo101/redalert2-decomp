// bool TActionClass::unknown_play_voice(...) (0x006B1180)
// Plays voice Data through Unknown_007158C0 (mode 2, -1); always true.
#include "shared/taction.hpp"

// @ref ?Unknown_007158C0@@YIXHHH@Z=007158c0
void __fastcall Unknown_007158C0(int voice, int arg2, int arg3);   // 0x007158C0 (plays a voice)

bool TActionClass::unknown_play_voice(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_007158C0(Data, 2, -1);
    return true;
}
