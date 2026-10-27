// UnknownTimeStamp_004d0040::UnknownTimeStamp_004d0040() -- 0x004D0040
// Purpose: records the current system time (timeGetTime) at +0x00. No
// direct callers (an out-of-line copy of an inline constructor). Owner not
// identified.
#include "shared/win32_api.hpp"
// @ref __imp__timeGetTime@0=0079a524

WIN32_IMPORT unsigned long __stdcall timeGetTime(void);

struct UnknownTimeStamp_004d0040 {
    UnknownTimeStamp_004d0040();

    unsigned long Time;     // +0x00
};

UnknownTimeStamp_004d0040::UnknownTimeStamp_004d0040()
{
    Time = timeGetTime();
}
