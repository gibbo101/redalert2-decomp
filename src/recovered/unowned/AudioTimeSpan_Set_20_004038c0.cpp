// void AudioTimeSpan::Set_20(__int64 value) -- 0x004038C0
// Purpose: sets the peak window.
#include "shared/audio.hpp"

void AudioTimeSpan::Set_20(__int64 value)
{
    PeakWindow = value;
}
