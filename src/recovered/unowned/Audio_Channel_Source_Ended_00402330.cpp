// int __fastcall Audio_Channel_Source_Ended(AudioChannel *channel) -- 0x00402330
// Purpose: the channel's default end-of-source handler (+0x160): while
// loops remain (-1 loops forever) counts one down and rewinds to the
// source's first piece; otherwise drops the source. Then runs the loop
// callback (+0xB4) and, when the channel still has a source, the driver's
// +0x24 entry. Returns 0.
// @ref ?Info@AudioSource@@QAEPAUAudioSourceInfo@@XZ=00408440
#include "shared/audio.hpp"

int __fastcall Audio_Channel_Source_Ended(AudioChannel *channel)
{
    if (channel->LoopCount != 0) {
        if (channel->LoopCount != -1) {
            channel->LoopCount--;
        }
        AudioSource *source = channel->Source;
        if (source != 0) {
            AudioSourceInfo *info = source->Info();
            channel->SourceInfo = info;
            if (info != 0) {
                channel->unknown_170 = info->unknown_0c;
                channel->unknown_178 = channel->unknown_174 = info->unknown_10;
                source->unknown_00 = 0;
            } else {
                channel->unknown_170 = channel->Source->unknown_00;
                channel->unknown_178 = channel->unknown_174 = channel->Source->unknown_04;
            }
        }
    } else {
        channel->Source = 0;
    }
    if (channel->unknown_loop_b4 != 0) {
        channel->unknown_loop_b4(channel);
    }
    if (channel->Source != 0) {
        channel->Driver->unknown_24(channel);
    }
    return 0;
}
