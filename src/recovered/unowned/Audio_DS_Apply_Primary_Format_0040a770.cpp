// void Audio_DS_Apply_Primary_Format() -- 0x0040A770
// Purpose: gives the primary DirectSound buffer the main device's default
// format (PCM) and restarts it looping.
#include "shared/crt_string.hpp"
#include "shared/audio.hpp"

void __fastcall Audio_DS_Apply_Primary_Format()
{
    AudioDevice *device = Audio_Get_Device();
    if (Audio_Primary_Buffer != 0 && device != 0) {
        Audio_Primary_Buffer->Stop();
        WAVEFORMATEX format;
        memset(&format, 0, sizeof(format));
        format.wFormatTag = WAVE_FORMAT_PCM;
        format.nChannels = (WORD)device->DefaultFormat.Channels;
        format.nSamplesPerSec = device->DefaultFormat.Rate;
        format.nBlockAlign = (WORD)(device->DefaultFormat.BytesPerSample * device->DefaultFormat.Channels);
        format.nAvgBytesPerSec = format.nBlockAlign * format.nSamplesPerSec;
        format.wBitsPerSample = (WORD)(device->DefaultFormat.BytesPerSample * 8);
        format.cbSize = 0;
        Audio_Primary_Buffer->SetFormat(&format);
        Audio_Primary_Buffer->Play(0, 0, DSBPLAY_LOOPING);
    }
}
