// int __fastcall Audio_Queue_Set_18(AudioQueue *queue, int value) -- 0x00408DD0
// Purpose: sets +0x18 (nonzero: the caller commits). Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Set_18(AudioQueue *queue, int value)
{
    queue->unknown_18 = value;
    return 0;
}
