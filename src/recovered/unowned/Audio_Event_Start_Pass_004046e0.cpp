// AudioSource *__fastcall Audio_Event_Start_Pass(AudioEvent *event) -- 0x004046E0
// Purpose: starts a pass over the event's samples: fills the play order with
// the sample indexes (without the intro of a sequence and the sustained last
// sample) and returns the first source to play: the intro of a sequence, or
// the next sample in order. 0 when there is nothing to play.
#include "shared/audio_event.hpp"

AudioSource *__fastcall Audio_Event_Start_Pass(AudioEvent *event)
{
    int index = 0;
    event->unknown_1e0 = event->SampleCount;
    if (event->unknown_1e0 == 0 || (event->Flags & 0x20)) {
        return 0;
    }
    AudioEventType *type = event->Type;
    if (type->unknown_58 < 0x21) {
        if (type->Flags & AUDIO_EVENT_TYPE_SEQUENCE) {
            event->unknown_1e0--;
            index = 1;
            event->unknown_ac = 0;
        } else {
            event->unknown_ac = -1;
        }
        if (type->Flags & AUDIO_EVENT_TYPE_SUSTAIN) {
            event->unknown_1e0--;
        }
        if (event->unknown_1e0 <= 0) {
            type->unknown_0c = 0;
            return 0;
        }
        for (int i = 0; i < event->unknown_1e0; i++, index++) {
            event->unknown_160[i] = index;
        }
        if ((event->Flags & 8) || !(event->Type->Flags & AUDIO_EVENT_TYPE_SEQUENCE)) {
            return Audio_Event_Next_Sample(event);
        }
    }
    return event->Samples[0]->Get_Source();
}
