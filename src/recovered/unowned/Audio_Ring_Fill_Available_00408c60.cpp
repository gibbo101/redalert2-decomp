// int __fastcall Audio_Ring_Fill_Available(AudioStream *ring) -- 0x00408C60
// Purpose: free bytes queued for filling that are not yet consumed.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Fill_Available(AudioStream *ring)
{
    int queued = ring->Queues[0].Queued;
    int consumed = ring->Queues[0].Consumed;
    return queued - consumed;
}
