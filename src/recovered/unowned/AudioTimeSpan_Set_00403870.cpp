// void AudioTimeSpan::Set(__int64 value) -- 0x00403870
// Purpose: sets the period and the late limit to value and the peak
// window to ten times the period.
// @ref __allmul=007820c0
#include "shared/audio.hpp"

void AudioTimeSpan::Set(__int64 value)
{
    unknown_00 = value;
    LateLimit = value;
    PeakWindow = unknown_00 * 10;
}
