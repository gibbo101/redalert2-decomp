// void __fastcall Audio_Device_Stop_Channels(AudioDevice *device, int id) -- 0x00403730
// Purpose: stops the device's channels with the given id (all of them for -1).
#include "shared/audio.hpp"

void __fastcall Audio_Device_Stop_Channels(AudioDevice *device, int id)
{
    AudioChannel *node = (AudioChannel *)Audio_List_First(&device->ChannelList);
    AudioChannel *channel = node;
    while (node != 0) {
        node = (AudioChannel *)Audio_List_Next(node);
        if (id == -1 || channel->unknown_0c == id) {
            Audio_Channel_Stop(channel);
        }
        channel = node;
    }
}
