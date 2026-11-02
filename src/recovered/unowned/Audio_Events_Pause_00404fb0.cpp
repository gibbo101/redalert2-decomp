// void Audio_Events_Pause() -- 0x00404FB0
// Purpose: pauses every event: one more pause on each, and a playing event
// (state 2) with its first pause moves its start time back by the current
// time.
// @ref ?Audio_Event_List@@3UAudioListNode@@A=00830ea0
// @ref ?Audio_Events_Ready@@3HA=00830fb8
// @ref ?Audio_Now@@YI_JXZ=004092d0
#include "shared/audio_event.hpp"

void Audio_Events_Pause()
{
    if (Audio_Events_Ready != 0) {
        for (AudioEvent *event = (AudioEvent *)Audio_Event_List.Next; event != (AudioEvent *)&Audio_Event_List;
             event = (AudioEvent *)event->Next) {
            if (event->PauseCount == 0 && event->State == 2) {
                event->unknown_140 -= Audio_Now();
            }
            event->PauseCount++;
        }
    }
}
