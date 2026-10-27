// void __fastcall Audio_Channel_Detach(AudioChannel *channel) -- 0x004028B0
// Purpose: takes the channel back from its device: unlinks it from the
// device's channel list and uncounts it, then unlinks it again while
// holding the device's busy count (+0x104, floored at 0 on release).
// @ref ?Audio_List_Remove@@YIXPAUAudioListNode@@@Z=00407380
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Detach(AudioChannel *channel)
{
    AudioDevice *device = channel->Device;
    Audio_List_Remove(channel);
    device->ChannelCount--;
    device->unknown_busy_104++;
    Audio_List_Remove(channel);
    if (--device->unknown_busy_104 < 0) {
        device->unknown_busy_104 = 0;
    }
}
