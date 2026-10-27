// void AudioFormat::Update_Rate() -- 0x004084D0
// Purpose: computes the bytes per second (a quarter of the PCM rate for the
// 4:1 ADPCM types 1 and 2).
#include "shared/audio.hpp"

void AudioFormat::Update_Rate()
{
    BytesPerSecond = BytesPerSample * Channels * Rate;
    if (Type == AUDIO_FORMAT_IMA_ADPCM || Type == 2) {
        BytesPerSecond >>= 2;
    }
}
