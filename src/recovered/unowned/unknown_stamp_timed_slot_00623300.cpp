// void __fastcall unknown_stamp_timed_slot_00623300(int index) -- 0x00623300
// Purpose: records the current timeGetTime() in record index of the table
// at 0x00AABDD0 (shared/unknown_timed_slots.hpp). Caller 0x00482540.
#include "shared/unknown_timed_slots.hpp"
#include "shared/win32_api.hpp"
// @ref ?unknown_timed_slots_aabdd0@@3PAUUnknownTimedSlot_aabdd0@@A=00aabdd0

void __fastcall unknown_stamp_timed_slot_00623300(int index)
{
    unknown_timed_slots_aabdd0[index].Time = timeGetTime();
}
