// void AudioSourceInfo::Detach() -- 0x00408520
// Purpose: forgets the piece's source.
#include "shared/audio.hpp"

void AudioSourceInfo::Detach()
{
    Source = 0;
}
