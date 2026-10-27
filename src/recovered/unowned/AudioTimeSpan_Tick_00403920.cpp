// void AudioTimeSpan::Tick(__int64 now) -- 0x00403920
// Purpose: records one mixer tick at time now: the elapsed time since the
// previous tick, the tick count, the peak elapsed time (restarted when it
// exceeds the peak window), late ticks (elapsed above the late limit) and
// the maximum elapsed time.
#include "shared/audio.hpp"

void AudioTimeSpan::Tick(__int64 now)
{
    __int64 elapsed = now - LastTime;
    Elapsed = elapsed;
    TickCount++;
    if ((unsigned __int64)Peak > (unsigned __int64)PeakWindow) {
        Peak = 0;
    }
    if ((unsigned __int64)elapsed > (unsigned __int64)Peak) {
        Peak = elapsed;
    }
    if ((unsigned __int64)elapsed > (unsigned __int64)LateLimit) {
        LateCount++;
    }
    if ((unsigned __int64)elapsed > (unsigned __int64)Maximum) {
        Maximum = elapsed;
    }
    LastTime = now;
}
