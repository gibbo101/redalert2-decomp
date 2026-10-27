// int __fastcall Audio_Channel_Set_Format(AudioChannel *channel, AudioFormat const *format) -- 0x00402800
// Purpose: records the channel's format (+0x17C); FormatChanged (+0x19C)
// tells whether it differed. Returns that flag.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_Channel_Set_Format(AudioChannel *channel, AudioFormat const *format)
{
    if (memcmp(format, &channel->Format, sizeof(AudioFormat)) == 0) {
        channel->FormatChanged = 0;
    } else {
        channel->FormatChanged = 1;
        channel->Format = *format;
    }
    return channel->FormatChanged;
}
