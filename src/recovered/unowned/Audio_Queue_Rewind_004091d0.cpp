// void __fastcall Audio_Queue_Rewind(AudioQueue *queue) -- 0x004091D0
// Purpose: resets the queue to its commit node (Audio_Queue_Reset expanded
// inline) and refreshes it.
#include "shared/audio.hpp"

void __fastcall Audio_Queue_Rewind(AudioQueue *queue)
{
    Audio_Queue_Reset(queue);
    Audio_Queue_Update(queue, 0);
}
