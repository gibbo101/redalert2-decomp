// unsigned char Event_Sequence() (0x004B5E80, name hypothesis)
// The event number within the current frame: 0 on the first call of a frame, then counting up.
#include "shared/event.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_event_frame_7d6684@@3HA=007d6684
// @ref ?unknown_event_counter_855b9c@@3EA=00855b9c

extern int unknown_event_frame_7d6684;                  // 0x007D6684
extern unsigned char unknown_event_counter_855b9c;      // 0x00855B9C

unsigned char Event_Sequence()
{
    if (Frame != unknown_event_frame_7d6684) {
        unknown_event_counter_855b9c = 0;
    }
    return unknown_event_counter_855b9c++;
}
