// int __fastcall Audio_Channel_Next_Piece(AudioChannel *channel) -- 0x004022C0
// Purpose: the channel's default next-block handler (+0x15C): with a
// next callback (+0xB0) returns its result, clearing +0x170..+0x178 when it
// is nonzero; otherwise steps to the next piece of the source and copies
// its words into +0x170 and +0x174/+0x178 (clearing +0x174 at the end).
// Returns 0 in that case.
// @ref ?Audio_List_Next_Unchecked@@YIPAUAudioListNode@@PAU1@@Z=004073a0
#include "shared/audio.hpp"

int __fastcall Audio_Channel_Next_Piece(AudioChannel *channel)
{
    if (channel->unknown_next_b0 != 0) {
        int result = channel->unknown_next_b0(channel);
        if (result != 0) {
            channel->unknown_174 = 0;
            channel->unknown_178 = 0;
            channel->unknown_170 = 0;
            return result;
        }
        return 0;
    }
    if (channel->SourceInfo != 0) {
        AudioSourceInfo *info = (AudioSourceInfo *)Audio_List_Next_Unchecked(channel->SourceInfo);
        channel->SourceInfo = info;
        if (info != 0) {
            channel->unknown_170 = info->unknown_0c;
            channel->unknown_178 = channel->unknown_174 = info->unknown_10;
            return 0;
        }
    }
    channel->unknown_174 = 0;
    return 0;
}
