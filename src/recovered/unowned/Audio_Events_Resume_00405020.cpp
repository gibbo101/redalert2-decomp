// void Audio_Events_Resume() -- 0x00405020
// Purpose: lifts one pause from every paused event; a playing event (state
// 2) whose pauses are all gone gets its start time moved forward by the
// current time.
// @ref ?Audio_Event_List@@3UAudioListNode@@A=00830ea0
// @ref ?Audio_Events_Ready@@3HA=00830fb8
// @ref ?Audio_Now@@YA_JXZ=004092d0
#include "shared/audio_event.hpp"

void Audio_Events_Resume()
{
    if (Audio_Events_Ready != 0) {
        for (AudioEvent *event = (AudioEvent *)Audio_Event_List.Next; event != (AudioEvent *)&Audio_Event_List;
             event = (AudioEvent *)event->Next) {
            if (event->PauseCount != 0) {
                if (--event->PauseCount < 0) {
                    event->PauseCount = 0;
                }
                if (event->PauseCount == 0 && event->State == 2) {
                    event->unknown_140 += Audio_Now();
                }
            }
        }
    }
}
