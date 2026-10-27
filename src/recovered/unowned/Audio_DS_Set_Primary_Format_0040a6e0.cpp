// void __fastcall Audio_DS_Set_Primary_Format(int rate, int bits, int channels) -- 0x0040A6E0
// Purpose: stops the primary buffer, sets it to PCM with the given rate,
// sample width and channel count, and plays it looping again.
// @ref ?Audio_Primary_Buffer@@3PAUIDirectSoundBuffer@@A=008315b0
#include "shared/audio.hpp"

void __fastcall Audio_DS_Set_Primary_Format(int rate, int bits, int channels)
{
    WAVEFORMATEX format;
    if (Audio_Primary_Buffer != 0) {
        format.wFormatTag = WAVE_FORMAT_PCM;
        format.nChannels = (WORD)channels;
        format.nSamplesPerSec = rate;
        format.nBlockAlign = (WORD)(bits / 8 * channels);
        format.nAvgBytesPerSec = format.nBlockAlign * rate;
        format.wBitsPerSample = (WORD)bits;
        format.cbSize = 0;
        Audio_Primary_Buffer->Stop();
        Audio_Primary_Buffer->SetFormat(&format);
        Audio_Primary_Buffer->Play(0, 0, DSBPLAY_LOOPING);
    }
}
