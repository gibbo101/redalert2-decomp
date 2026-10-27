// void __fastcall Audio_Event_Handle_Stop_Clear(AudioEventHandle *handle) -- 0x00405c10
// Purpose: stops the event a handle stands for (when the handle is still
// good) and also clears the handle's token.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Handle_Stop_Clear(AudioEventHandle *handle)
{
    if (Audio_Events_Ready != 0 && handle->Token == &Audio_Event_Bag && handle->Event != 0) {
        AudioEvent *event = handle->Event;
        if (handle->Type == event->Type && handle->Serial == event->unknown_138
            && !(event->Flags & AUDIO_EVENT_STOPPED)) {
            AUDIO_EVENT_DETACH_INLINE(event)
            AUDIO_EVENT_RELEASE_SAMPLES_INLINE(event)
            AUDIO_EVENT_MARK_STOPPED(event)
        }
        handle->Event = 0;
    }
    handle->Type = 0;
    handle->Token = 0;
}
