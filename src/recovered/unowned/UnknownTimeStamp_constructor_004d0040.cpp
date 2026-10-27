// UnknownTimeStamp_004d0040::UnknownTimeStamp_004d0040() -- 0x004D0040
// Purpose: records the current system time (timeGetTime) at +0x00. No
// direct callers (the out-of-line copy of the constructor the global
// 0x00866074's initializer expands). Owner not identified.
#include "shared/unknown_time_stamp.hpp"
#include "shared/win32_api.hpp"

UnknownTimeStamp_004d0040::UnknownTimeStamp_004d0040()
{
    Time = timeGetTime();
}
