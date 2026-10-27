// AudioChannel *__fastcall Audio_Device_Create_Channel(AudioDevice *device, int flags) -- 0x004036C0
// Purpose: takes a channel for a new sound (0x004035F0 with id 1) and
// releases it with the given value (0x00402440). Returns the channel, or 0.
#include "shared/audio.hpp"

AudioChannel *__fastcall Audio_Device_Create_Channel(AudioDevice *device, int flags)
{
    AudioChannel *channel = Audio_Device_Find_Channel(device, 1);
    if (channel != 0) {
        Audio_Channel_Release(channel, flags);
    }
    return channel;
}
