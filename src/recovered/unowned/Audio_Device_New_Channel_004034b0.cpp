// AudioChannel *__fastcall Audio_Device_New_Channel(AudioDevice *device) -- 0x004034B0
// Purpose: makes one more channel for the device unless it already has its
// maximum (+0xF4) and adds it (0x00402860, expanded inline). Returns the
// channel, or 0.
#include "shared/audio.hpp"

AudioChannel *__fastcall Audio_Device_New_Channel(AudioDevice *device)
{
    AudioChannel *channel;
    if (device->ChannelCount >= device->unknown_f4) {
        goto fail;
    }
    channel = Audio_Channel_Create(device);
    if (channel == 0) {
fail:
        return 0;
    }
    Audio_Device_Add_Channel(device, channel);
    return channel;
}
