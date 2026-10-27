// void __fastcall Audio_Ring_Reset(AudioStream *ring) -- 0x00408990
// Purpose: gives every node its whole buffer as both windows and numbers
// the nodes, then starts both queues at the first node (Queued and
// Consumed -1001, nothing pending) with the whole ring queued for
// filling.
#include "shared/audio.hpp"

void __fastcall Audio_Ring_Reset(AudioStream *ring)
{
    AudioStreamNode *first = Audio_Ring_Number_Nodes(ring);
    for (int side = 0; side < 2; side++) {
        AudioQueue *queue = &ring->Queues[side];
        queue->Restart(first);
    }
    ring->Queues[0].Queued += ring->Size;
}
