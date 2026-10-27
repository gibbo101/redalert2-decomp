// void AudioTimeSpan::Set_08(__int64 value) -- 0x004038A0
// Purpose: sets the late limit.
#include "shared/audio.hpp"

void AudioTimeSpan::Set_08(__int64 value)
{
    LateLimit = value;
}
