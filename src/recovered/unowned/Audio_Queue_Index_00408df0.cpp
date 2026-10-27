// int __fastcall Audio_Queue_Index(AudioQueue *queue) -- 0x00408DF0
// Purpose: the queue's side (0 fill, 1 drain).
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Index(AudioQueue *queue)
{
    return queue->Index;
}
