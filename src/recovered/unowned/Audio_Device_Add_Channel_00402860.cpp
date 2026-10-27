// void __fastcall Audio_Device_Add_Channel(AudioDevice *device, AudioChannel *channel) -- 0x00402860
// Purpose: gives the channel to the device: sets its device, counts it and
// links it at the tail of the device's channel list, holding the device's
// busy count (+0x104, floored at 0 on release) meanwhile.
// @ref ?Audio_List_Add_Tail@@YIXPAUAudioListNode@@0@Z=00407350
#include "shared/audio.hpp"

void __fastcall Audio_Device_Add_Channel(AudioDevice *device, AudioChannel *channel)
{
    channel->Device = device;
    device->ChannelCount++;
    device->unknown_busy_104++;
    Audio_List_Add_Tail(&device->ChannelList, channel);
    if (--device->unknown_busy_104 < 0) {
        device->unknown_busy_104 = 0;
    }
}
