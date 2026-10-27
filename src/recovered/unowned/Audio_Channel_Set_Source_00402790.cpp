// void __fastcall Audio_Channel_Set_Source(AudioChannel *channel, AudioSource *source) -- 0x00402790
// Purpose: attaches a source to the channel. When the source has info
// (0x00408440) the channel keeps it and copies its +0x0C and +0x10 words
// into +0x170 and +0x174/+0x178, clearing the source's first word;
// otherwise the source's own two words are copied there.
// @ref ?Info@AudioSource@@QAEPAUAudioSourceInfo@@XZ=00408440
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Set_Source(AudioChannel *channel, AudioSource *source)
{
    channel->Source = source;
    if (source != 0) {
        AudioSourceInfo *info = source->Info();
        channel->SourceInfo = info;
        if (info != 0) {
            channel->unknown_170 = info->unknown_0c;
            channel->unknown_178 = channel->unknown_174 = info->unknown_10;
            source->unknown_00 = 0;
            return;
        }
        channel->unknown_170 = channel->Source->unknown_00;
        channel->unknown_178 = channel->unknown_174 = channel->Source->unknown_04;
    }
}
