// void __fastcall Audio_Event_Handle_Stop_Loop(AudioEventHandle *handle) -- 0x00405E90
// Purpose: stops the handle's event when its type loops forever (flag 1 and no
// loop count) and forgets the event; other events keep the handle's event.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Handle_Stop_Loop(AudioEventHandle *handle)
{
    AudioEvent *event = Audio_Event_Resolve(handle);
    if (event != 0 && (event->Type->Flags & AUDIO_EVENT_TYPE_LOOPS) && event->Type->LoopCount == 0) {
        Audio_Event_Stop(event);
        handle->Event = 0;
    }
    handle->Type = 0;
}
