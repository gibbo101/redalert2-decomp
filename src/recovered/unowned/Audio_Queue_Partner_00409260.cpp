// AudioQueue *__fastcall Audio_Queue_Partner(AudioQueue *queue) -- 0x00409260
// Purpose: the ring's other queue.
#include "shared/audio.hpp"

AudioQueue *__fastcall Audio_Queue_Partner(AudioQueue *queue)
{
    int other = queue->Index + 1;
    if (other == 2) {
        other = 0;
    }
    return &queue->Stream->Queues[other];
}
