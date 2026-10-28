// AudioSource *__fastcall Audio_Event_Next_Sample(AudioEvent *event) -- 0x00404790
// Purpose: moves an event on to its next sample: a random event draws one of the
// entries left in its order, others take the following one; a sustained event
// whose samples are used up repeats, a looping event starts another pass.
#include "shared/audio_event.hpp"
// @ref ?Audio_Event_Start_Pass@@YIPAUAudioSource@@PAUAudioEvent@@@Z=004046e0
// @ref ?Get_Source@AudioBankEntry@@QAIPAUAudioSource@@XZ=00402030

AudioSource *__fastcall Audio_Event_Next_Sample(AudioEvent *event)
{
    AudioEventType *type = event->Type;
    unsigned int flags = type->Flags;
    if (type->unknown_58 < 0x21 || (event->Flags & 0x20)) {
        if (event->unknown_1e0 != 0 && !(event->Flags & 0x20)) {
            if (flags & AUDIO_EVENT_TYPE_RANDOM) {
                int index = unknown_random_839218(0, event->unknown_1e0 - 1);
                event->unknown_ac = event->unknown_160[index];
                for (int i = index; i < event->unknown_1e0 - 1; i++) {
                    event->unknown_160[i] = event->unknown_160[i + 1];
                }
            } else {
                event->unknown_ac++;
            }
            event->unknown_1e0--;
            return event->Samples[event->unknown_ac]->Get_Source();
        }
        if ((flags & AUDIO_EVENT_TYPE_LOOPS) && !(event->Flags & 0x20)
            && (type->LoopCount == 0 || event->unknown_1e4 < type->LoopCount - 1)) {
            event->unknown_1e4++;
            return Audio_Event_Start_Pass(event);
        }
        if ((flags & AUDIO_EVENT_TYPE_SUSTAIN) && !(event->Flags & 0x10) && event->SampleCount >= 1) {
            event->Flags |= 0x10;
            return event->Samples[event->SampleCount - 1]->Get_Source();
        }
    }
    return 0;
}
