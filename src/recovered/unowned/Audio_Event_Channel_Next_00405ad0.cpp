// int __fastcall Audio_Event_Channel_Next(AudioChannel *channel) -- 0x00405AD0
// Purpose: channel callback of an event: picks the next sample and either
// plays it straight away or, for events with a random delay, parks it until
// the delay has passed.
#include "shared/audio_event.hpp"

int __fastcall Audio_Event_Channel_Next(AudioChannel *channel)
{
    AudioEvent *event = (AudioEvent *)channel->Owner;
    AudioSource *source = Audio_Event_Next_Sample(event);

    if (event->Type->unknown_5c < 0x21) {
        Audio_Channel_Set_Source(channel, source);
        return 0;
    }
    Audio_Channel_Set_Source(channel, 0);
    AudioEventType *type = event->Type;
    if ((type->Flags & 0x88) == 0 || source != 0 || event->unknown_268 != 0) {
        unsigned int hi = type->unknown_5c;
        unsigned int lo = type->unknown_58;
        unsigned int delay = unknown_random_839218(lo, hi);
        if (delay < 0x21) {
            Audio_Channel_Set_Source(channel, source);
            return 0;
        }
        event->unknown_13c = delay;
        event->unknown_148 = (int)source;
    }
    return 0;
}
