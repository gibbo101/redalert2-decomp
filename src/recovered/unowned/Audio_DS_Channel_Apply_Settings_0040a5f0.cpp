// int __fastcall Audio_DS_Channel_Apply_Settings(AudioChannel *channel) -- 0x0040A5F0
// Purpose: pushes the channel's settings to its buffer: volume (0..100%)
// through the attenuation table, pan (-100..100) through the same table
// mirrored, and the source rate scaled by the frequency level.
// Returns 0.
// @ref ?Audio_Attenuation@@3QBJB=007cce48
// @ref ?Scale_Frequency@AudioLevelSet@@QAIHH@Z=00401190
#include "shared/audio.hpp"

int __fastcall Audio_DS_Channel_Apply_Settings(AudioChannel *channel)
{
    AudioChannelBuffer *record = channel->DriverBuffer;
    record->Buffer->SetVolume(Audio_Attenuation[((channel->Settings.Volume.Current >> 16) * 100) >> 14]);
    int pan = (int)((((channel->Settings.Pan.Current >> 16) * 200) >> 14) - 100);
    if (pan < 0) {
        record->Buffer->SetPan(Audio_Attenuation[100 + pan]);
    } else {
        record->Buffer->SetPan(-Audio_Attenuation[100 - pan]);
    }
    DWORD frequency = channel->Settings.Scale_Frequency(record->Channel->Format.Rate);
    record->Buffer->SetFrequency(frequency);
    return 0;
}
