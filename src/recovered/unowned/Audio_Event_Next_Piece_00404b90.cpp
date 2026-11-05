#include "shared/audio_event.hpp"
static int Audio_Random(int low, int high);
int __fastcall Audio_Event_Next_Piece(AudioEvent *event)
{
    AudioEventType *type = event->Type;
    unsigned int flags = type->Flags;
    if (event->unknown_268 == event->unknown_270) {
        int count = 0;
        if (((type->Flags & AUDIO_EVENT_TYPE_LOOPS) == 0 && event->unknown_26c == 1) ||
            ((type->Flags & AUDIO_EVENT_TYPE_LOOPS) != 0 && type->LoopCount != 0 && event->unknown_26c >= type->LoopCount)) return -1;
        if (type->Intro != 0 && (event->Flags & 8) == 0) {
            event->Order[count++] = Audio_Random(0, type->Intro - 1);
        }
        if (type->Flags & 4) {
            for (int piece = type->Intro; piece < type->SampleCount - type->Outro; ++piece) {
                event->Order[count++] = piece;
            }
        } else {
            int piece;
            if (type->Flags & AUDIO_EVENT_TYPE_RANDOM) {
                if (event->unknown_26c == 0) {
                    piece = Audio_Random(type->Intro, type->SampleCount - type->Outro - 1);
                    event->unknown_274 = piece;
                } else piece = event->unknown_274;
            } else piece = type->Intro;
            event->Order[count++] = piece;
        }
        event->unknown_268 = count;
        event->unknown_270 = 0;
        ++event->unknown_26c;
    }
    int piece;
    if (flags & AUDIO_EVENT_TYPE_RANDOM) {
        if (type->Intro != 0 && (event->Flags & 8) == 0 && event->unknown_270 <= 0) {
            goto sequential_piece;
        }
        int low = type->Intro != 0 && (event->Flags & 8) == 0 ? 1 : 0;
        int pick = Audio_Random(low, event->unknown_268 - 1);
        piece = event->Order[pick];
        for (int i = pick; i < event->unknown_268 - 1; ++i) event->Order[i] = event->Order[i + 1];
        --event->unknown_268;
    } else {
sequential_piece:
        piece = event->Order[event->unknown_270++];
    }
    return piece;
}
