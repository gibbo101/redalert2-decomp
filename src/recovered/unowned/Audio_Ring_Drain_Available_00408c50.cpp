// int __fastcall Audio_Ring_Drain_Available(AudioStream *ring) -- 0x00408C50
// Purpose: bytes queued for draining that are not yet consumed.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Drain_Available(AudioStream *ring)
{
    int queued = ring->Queues[1].Queued;
    int consumed = ring->Queues[1].Consumed;
    return queued - consumed;
}
