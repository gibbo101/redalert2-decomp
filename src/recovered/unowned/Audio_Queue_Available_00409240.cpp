// int __fastcall Audio_Queue_Available(AudioQueue *queue) -- 0x00409240
// Purpose: the bytes queued to this queue that it has not committed yet
// (Queued minus Consumed).
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Available(AudioQueue *queue)
{
    int queued = queue->Queued;
    int consumed = queue->Consumed;
    return queued - consumed;
}
