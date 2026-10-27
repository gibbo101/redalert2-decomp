// AudioQueue *__fastcall Audio_Ring_Acquire(AudioStream *ring, int index) -- 0x00408B50
// Purpose: acquires queue index of the ring (0 "Write", 1 "Read"); the
// first acquisition resets the ring. Returns 0 (reported) when that queue
// is already acquired.
// @ref ??_C@_0DG@GPDE@?$CFs?5access?5to?5stream?5failed?4?5Acce@=007ccd9c
// @ref ??_C@_04KCBC@Read?$AA@=007ccdd4
// @ref ??_C@_05DHHK@Write?$AA@=007ccddc
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"


AudioQueue *__fastcall Audio_Ring_Acquire(AudioStream *ring, int index)
{
    AudioQueue *queue = &ring->Queues[index];
    if (queue->Users != 0) {
        Debug_Printf("%s access to stream failed. Access already acquired.\n", queue->Index == 0 ? "Write" : "Read");
        return 0;
    }
    if (ring->Users == 0) {
        Audio_Ring_Reset(ring);
    }
    queue->Users++;
    ring->Users++;
    return queue;
}
