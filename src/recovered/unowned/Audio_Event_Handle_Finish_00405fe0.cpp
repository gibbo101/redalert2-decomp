// void __fastcall Audio_Event_Handle_Finish(AudioEventHandle *handle) -- 0x00405FE0
// Purpose: lets the handle's event finish (it stops after the sample being
// played) and forgets the event; a stale handle just forgets it.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Handle_Finish(AudioEventHandle *handle)
{
    AudioEvent *event = Audio_Event_Resolve(handle);
    if (event != 0) {
        Audio_Event_Finish(event);
        handle->Event = 0;
    }
    handle->Type = 0;
}
