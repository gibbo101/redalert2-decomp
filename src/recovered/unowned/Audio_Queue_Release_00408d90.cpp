// void __fastcall Audio_Queue_Release(AudioQueue *queue) -- 0x00408D90
// Purpose: drops an acquisition of the queue and of its ring (each
// floored at 0).
#include "shared/audio.hpp"

void __fastcall Audio_Queue_Release(AudioQueue *queue)
{
    if (--queue->Users < 0) {
        queue->Users = 0;
    }
    if (--queue->Stream->Users < 0) {
        queue->Stream->Users = 0;
    }
}
