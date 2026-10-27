// int UnknownTimeStamp_004d0040::unknown_elapsed() const -- 0x004D0050
// Purpose: milliseconds since the recorded time (+0x00), computed across a
// timeGetTime wrap (one less when the clock has wrapped). No direct callers;
// same type as the constructor 0x004D0040.
#include "shared/win32_api.hpp"
// @ref __imp__timeGetTime@0=0079a524

WIN32_IMPORT unsigned long __stdcall timeGetTime(void);

struct UnknownTimeStamp_004d0040 {
    int unknown_elapsed_004d0050() const;

    unsigned long Time;     // +0x00
};

int UnknownTimeStamp_004d0040::unknown_elapsed_004d0050() const
{
    unsigned long now = timeGetTime();
    if (now <= Time) {
        return now - Time - 1;
    }
    return now - Time;
}
