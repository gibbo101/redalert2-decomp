// int Audio_Device_Update(AudioDevice *device) (0x00402F60)
// The device's update function (+0x10C until the device is run): returns
// 0x80120000 while the device is busy; once the level span is due, ticks it,
// updates the device levels (and the optional +0xE8 set) and, for every
// playing channel with a source whose own or linked levels changed (or when
// the device levels did), recombines the channel's settings and has its
// driver apply them; then clears the changed flags of the device levels.
// @ref ?Changed@AudioLevelSet@@QAEHXZ=004010a0
// @ref ?Clear_Changed@AudioLevelSet@@QAEXXZ=00401170
#include "shared/audio.hpp"

int __fastcall Audio_Device_Update(AudioDevice *device)
{
    if (device->unknown_busy_104 != 0) {
        return 0x80120000;
    }
    __int64 now = Audio_Now();
    if (!device->LevelSpan.Is_Due(now)) {
        return 0;
    }
    device->LevelSpan.Tick(now);
    device->Levels.Update();
    if (device->unknown_levels_e8 != 0) {
        device->unknown_levels_e8->Update();
    }
    int changed;
    if (device->unknown_levels_e8 == 0 || (changed = device->unknown_levels_e8->Changed()) == 0) {
        changed = device->Levels.Changed();
    }
    AudioChannel *channel = (AudioChannel *)device->ChannelList.Next;
    while (channel != (AudioChannel *)&device->ChannelList) {
        AudioChannel *next = (AudioChannel *)channel->Next;
        if ((channel->Flags & AUDIO_CHANNEL_PLAYING) && channel->Source != 0) {
            channel->Levels.Update();
            if (changed || channel->Levels.Changed()
                || (channel->unknown_levels_94 != 0 && channel->unknown_levels_94->Changed())
                || (channel->unknown_levels_98 != 0 && channel->unknown_levels_98->Changed())
                || (channel->unknown_levels_9c != 0 && channel->unknown_levels_9c->Changed())
                || (channel->unknown_levels_90 != 0 && channel->unknown_levels_90->Changed())) {
                Audio_Channel_Update_Settings(channel);
                channel->Driver->Apply_Settings(channel);
            }
        }
        channel = next;
    }
    if (device->unknown_levels_e8 != 0) {
        device->unknown_levels_e8->Clear_Changed();
    }
    device->Levels.Clear_Changed();
    return 0;
}
