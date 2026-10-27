// void __fastcall Audio_Device_Resume_Channels(AudioDevice *device, int id) -- 0x004037C0
// Purpose: resumes the device's paused channels with the given id (all of
// them for -1).
#include "shared/audio.hpp"

void __fastcall Audio_Device_Resume_Channels(AudioDevice *device, int id)
{
    AudioListCursor cursor;
    cursor.First(&device->ChannelList);
    for (AudioChannel *channel = (AudioChannel *)cursor.Node; channel != 0; channel = (AudioChannel *)cursor.Next()) {
        if ((channel->Flags & AUDIO_CHANNEL_PAUSED) && (id == -1 || channel->unknown_0c == id)) {
            Audio_Channel_Resume(channel);
        }
    }
}
