// int __fastcall Audio_Queue_Get_18(AudioQueue *queue) -- 0x00408DE0
// Purpose: returns +0x18.
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Get_18(AudioQueue *queue)
{
    return queue->unknown_18;
}
