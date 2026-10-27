// int __fastcall Audio_Device_Destroy_Channels(AudioDevice *device, int id) -- 0x004036F0
// Purpose: destroys the device's channels with the given id (all of them
// for -1). Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_Device_Destroy_Channels(AudioDevice *device, int id)
{
    AudioChannel *node = (AudioChannel *)Audio_List_First(&device->ChannelList);
    AudioChannel *channel = node;
    while (node != 0) {
        node = (AudioChannel *)Audio_List_Next(node);
        if (id == -1 || channel->unknown_0c == id) {
            Audio_Channel_Destroy(channel);
        }
        channel = node;
    }
    return 0;
}
