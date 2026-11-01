// void __fastcall Audio_Event_Update(AudioEvent *event) -- 0x004055D0
// Purpose: steps one event's state machine: 0 asks for a channel and sets
// it up (random frequency and volume, an optional random delay), 2 waits
// out the delay, 3 stops a finished one-shot loop whose handle is gone, a
// pending restart (flag 0x40) stops the channel and plays the next sample,
// and 4 stops the event. Audio off forces state 4.
// @ref ?Audio_Event_Channel_Done@@YIHPAUAudioChannel@@@Z=00405a10
// @ref ?Audio_Event_Channel_End@@YIHPAUAudioChannel@@@Z=00405a00
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
#include "shared/audio_event.hpp"

static int Audio_Random(int low, int high)
{
    return unknown_random_839218(low, high);
}

static void Audio_Event_Start(AudioEvent *event)
{
    AudioEventType *type = event->Type;
    if (type->SampleCount != 0 && type->unknown_0c != 0) {
        event->unknown_1e4 = 0;
        event->Channel = Audio_Event_Start_Channel(type->unknown_40 + event->unknown_154, 0);
        if (event->Channel != 0) {
            event->unknown_14c = Audio_Random(type->unknown_60, type->unknown_64) + 100;
            event->unknown_150 = Audio_Random(0, type->unknown_68);
            Audio_Channel_Set_Flag_10(event->Channel);
            event->Channel->Owner = event;
            event->Channel->unknown_loop_b4 = Audio_Event_Channel_Next;
            event->Channel->unknown_done_b8 = Audio_Event_Channel_Done;
            event->Channel->unknown_end_callback_bc = Audio_Event_Channel_End;
            event->State = 1;
            event->Channel->unknown_levels_90 = &event->Levels;
            event->Channel->unknown_levels_98 = &Audio_Event_Levels;
            event->Channel->unknown_levels_9c = Audio_Global_Levels[7];
            if (type->Flags & 0x88) {
                int delay = Audio_Random((type->Flags & 0x80) ? 0x21 : type->unknown_58, type->unknown_5c);
                if (delay >= 0x21) {
                    __int64 wait = delay;
                    event->unknown_20 = 1;
                    if (event->PauseCount != 0) {
                        event->unknown_140 = wait;
                    } else {
                        event->unknown_140 = Audio_Now() + wait;
                    }
                    event->State = 2;
                }
            }
            return;
        }
    }
    Audio_Event_Stop(event);
    return;
}

void __fastcall Audio_Event_Update(AudioEvent *event)
{
    if (Audio_Enabled == 0) {
        event->State = 4;
    }
again:
    switch (event->State) {
    case 2:
        if (event->Flags & 0x40) {
            goto restart;
        }
        if (event->PauseCount != 0) {
            return;
        }
        if ((unsigned __int64)Audio_Now() <= (unsigned __int64)event->unknown_140) {
            return;
        }
        event->State = event->unknown_20;
        goto again;

    case 0:
        Audio_Event_Start(event);
        return;

    case 3:
        if ((event->Type->Flags & AUDIO_EVENT_TYPE_LOOPS) && event->Type->LoopCount == 0 && !(event->Flags & 0x20)) {
            if (event->unknown_278 == 0 || Audio_Event_Resolve(event->unknown_278) != event) {
                Audio_Event_Stop(event);
            }
        }
        if (event->Flags & 0x40) {
        restart:
            AudioChannel *channel = event->Channel;
            if (channel != 0) {
                Audio_Channel_Lock(channel);
                event->Flags &= ~0x40;
                Audio_Channel_Stop(event->Channel);
                if ((event->Type->Flags & AUDIO_EVENT_TYPE_SUSTAIN) && !(event->Flags & 0x10)) {
                    event->State = 1;
                    event->unknown_148 = (int)Audio_Event_Next_Sample(event);
                    if (event->PauseCount == 0 && Audio_Event_Begin(event) == 0) {
                        Audio_Event_Stop(event);
                    }
                }
                Audio_Channel_Unlock(channel);
            } else {
                event->Flags &= ~0x40;
            }
        }
        break;

    case 4:
        Audio_Event_Stop(event);
        break;

    case 1:
        break;
    }
}
