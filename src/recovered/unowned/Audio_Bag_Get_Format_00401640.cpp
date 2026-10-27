// void __fastcall Audio_Bag_Get_Format(AudioBag *bag, int index, AudioFormat *format) -- 0x00401640
// Purpose: describes entry index's sound: IMA ADPCM when flagged (2 bytes
// a sample), else PCM of one or, flagged, two bytes a sample; mono or, when
// flagged, stereo.
#include "shared/audio.hpp"

void __fastcall Audio_Bag_Get_Format(AudioBag *bag, int index, AudioFormat *format)
{
    AudioBagEntry *entry = &bag->Entries[index];
    format->unknown_00 = 4;
    format->Rate = entry->Rate;
    format->Channels = (entry->Flags & AUDIO_BAG_STEREO) ? 2 : 1;
    format->BlockSize = entry->BlockSize;
    if (entry->Flags & AUDIO_BAG_ADPCM) {
        format->Type = AUDIO_FORMAT_IMA_ADPCM;
        format->BytesPerSample = 2;
    } else {
        format->Type = AUDIO_FORMAT_PCM;
        format->BytesPerSample = (entry->Flags & AUDIO_BAG_16_BIT) ? 2 : 1;
    }
}
