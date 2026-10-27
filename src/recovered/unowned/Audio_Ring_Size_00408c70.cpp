// int __fastcall Audio_Ring_Size(AudioStream *ring) -- 0x00408C70
// Purpose: the ring's size in bytes.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Size(AudioStream *ring)
{
    return ring->Size;
}
