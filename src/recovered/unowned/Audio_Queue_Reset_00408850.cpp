// void __fastcall Audio_Queue_Reset(AudioQueue *queue) -- 0x00408850
// Purpose: moves the queue back to its commit node, dropping what was
// pending.
#include "shared/audio.hpp"

void __fastcall Audio_Queue_Reset(AudioQueue *queue)
{
    queue->Pending = 0;
    queue->Node = queue->CommitNode;
    if (queue->Node != 0) {
        queue->Pointer = queue->Node->Windows[queue->Index].Pointer;
    } else {
        queue->Pointer = 0;
    }
    queue->Available = 0;
    queue->Flags &= ~AUDIO_QUEUE_AT_HEAD;
}
