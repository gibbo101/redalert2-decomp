// void __fastcall Audio_Event_Detach(AudioEvent *event) -- 0x00404120
// Purpose: takes the event off the channel that plays it (when the channel
// still belongs to the event): stops the channel if the event was started,
// clears its flag 0x10, handlers, owner and levels.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Detach(AudioEvent *event)
{
    if (event->Channel != 0 && event == event->Channel->Owner) {
        if (event->Flags & 2) {
            Audio_Channel_Stop(event->Channel);
        }
        Audio_Channel_Clear_Flag_10(event->Channel);
        event->Channel->Owner = 0;
        event->Channel->unknown_end_callback_bc = 0;
        event->Channel->unknown_loop_b4 = 0;
        event->Channel->unknown_done_b8 = 0;
        event->Channel->unknown_levels_90 = 0;
        event->Channel->unknown_levels_98 = 0;
        event->Channel->unknown_levels_9c = 0;
        event->Channel = 0;
    }
}
