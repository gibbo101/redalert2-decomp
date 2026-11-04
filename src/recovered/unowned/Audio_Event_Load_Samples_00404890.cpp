// Acquire the bank samples needed for the event's next playback pass (0x00404890).
#include "shared/audio_event.hpp"
static int Audio_Random(int low, int high);
// @ref ?Audio_Event_Next_Piece@@YIHPAUAudioEvent@@@Z=00404b90
void __fastcall Audio_Event_Load_Samples(AudioEvent *event)
{
    AudioEventType *type = event->Type;
    if (event->SampleCount != 0) {
        if (type->unknown_58 < 33) return;
        for (int i = 0; i < event->SampleCount; ++i) {
            ((AudioCountedList *)event->Samples[i])->Leave();
            event->Samples[i] = 0;
        }
        event->SampleCount = 0;
    }
    int piece;
    if (type->unknown_58 < 33) {
        if (type->Intro != 0) {
            piece = Audio_Random(0, type->Intro - 1);
            event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
            if (event->Samples[event->SampleCount]) {
                ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                ++event->SampleCount;
            }
        }
        if (type->Flags & 4) {
            for (piece = type->Intro; piece < type->SampleCount - type->Outro; ++piece) {
                event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
                if (event->Samples[event->SampleCount]) {
                    ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                    ++event->SampleCount;
                }
            }
        } else {
            if (type->Flags & AUDIO_EVENT_TYPE_RANDOM) {
                piece = Audio_Random(type->Intro, type->SampleCount - type->Outro - 1);
                event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
                if (event->Samples[event->SampleCount]) {
                    ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                    ++event->SampleCount;
                }
            } else {
                piece = type->Intro;
                event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
                if (event->Samples[event->SampleCount]) {
                    ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                    ++event->SampleCount;
                }
            }
        }
        if (type->Outro == 0) return;
        piece = Audio_Random(type->SampleCount - type->Outro, type->SampleCount - 1);
        event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
        if (event->Samples[event->SampleCount]) {
            ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
            ++event->SampleCount;
        }
        return;
    } else {
        int outro = -1;
        if (type->Outro != 0 && (type->Flags & AUDIO_EVENT_TYPE_SUSTAIN)) {
            outro = Audio_Random(type->SampleCount - type->Outro, type->SampleCount - 1);
        }
        piece = Audio_Event_Next_Piece(event);
        if (piece >= 0) {
            event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[piece]);
            if (event->Samples[event->SampleCount]) {
                ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                ++event->SampleCount;
            }
            if (outro != -1) {
                event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[outro]);
                if (event->Samples[event->SampleCount]) {
                    ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                    ++event->SampleCount;
                }
            }
        } else {
            if (outro == -1 || (event->Flags & 0x10)) return;
            event->Samples[event->SampleCount] = Audio_Bank_Load(Audio_Event_Bank, event->Type->Samples[outro]);
            if (event->Samples[event->SampleCount]) {
                ((AudioCountedList *)event->Samples[event->SampleCount])->Enter();
                ++event->SampleCount;
            }
            event->Flags |= 0x10;
        }
    }
}
