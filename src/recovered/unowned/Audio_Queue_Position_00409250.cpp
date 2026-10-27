// int __fastcall Audio_Queue_Position(AudioQueue *queue) -- 0x00409250
// Purpose: the queue's offset in the ring.
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Position(AudioQueue *queue)
{
    return queue->Position;
}
