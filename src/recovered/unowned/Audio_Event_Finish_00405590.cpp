// void __fastcall Audio_Event_Finish(AudioEvent *event) -- 0x00405590
// Purpose: marks an event that is not finished yet (flag 0x20) finished
// and not to be started (flags 0x60); when its channel is still its own the
// channel is unlocked in the driver.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Finish(AudioEvent *event)
{
    if (!(event->Flags & 0x20)) {
        if (event->Channel != 0 && event == event->Channel->Owner) {
            Audio_Channel_Lock(event->Channel);
            event->Flags |= 0x60;
            Audio_Channel_Unlock(event->Channel);
        } else {
            event->Flags |= 0x60;
        }
    }
}
