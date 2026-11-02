// unsigned long unknown_ticks_004d0090() (0x004D0090)
// Game ticks (1/60 s) elapsed since the startup time stamp 0x00866074.
#include "shared/unknown_time_stamp.hpp"

unsigned long unknown_ticks_004d0090()
{
    return (unsigned long)unknown_time_stamp_866074.unknown_elapsed_004d0050() * 3 / 50;
}
