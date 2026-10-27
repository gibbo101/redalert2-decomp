// int UnknownTimeStamp_004d0040::unknown_elapsed_004d0050() const -- 0x004D0050
// Purpose: milliseconds since the recorded time (+0x00), computed across a
// timeGetTime wrap (one less when the clock has wrapped). No direct callers.
#include "shared/unknown_time_stamp.hpp"
#include "shared/win32_api.hpp"

int UnknownTimeStamp_004d0040::unknown_elapsed_004d0050() const
{
    unsigned long now = timeGetTime();
    if (now <= Time) {
        return now - Time - 1;
    }
    return now - Time;
}
