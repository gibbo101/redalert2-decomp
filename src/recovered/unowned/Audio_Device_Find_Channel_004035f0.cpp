// AudioChannel *__fastcall Audio_Device_Find_Channel(AudioDevice *device, int id) -- 0x004035F0
// Purpose: picks a channel of the device (id -1 means 1) to take a new
// sound: the first one that is neither playing, paused nor flagged 0x10, or
// else the lowest priority (+0xA0) one among the others, preferring a
// stopped one over a playing one of equal or higher priority; among playing
// ones of equal priority the quieter (combined volume) is taken, but only
// when it is at least 0x666 quieter.
#include "shared/audio.hpp"

AudioChannel *__fastcall Audio_Device_Find_Channel(AudioDevice *device, int id)
{
    if (id == -1) {
        id = 1;
    }
    int idle_priority = 0x7f;
    AudioChannel *idle = 0;
    int playing_priority = 0x7f;
    AudioChannel *playing = 0;
    unsigned int playing_volume = (unsigned int)-1;
    AudioListCursor cursor;
    cursor.First(&device->ChannelList);
    AudioChannel *channel;
    for (channel = (AudioChannel *)cursor.Node; channel != 0; channel = (AudioChannel *)cursor.Next()) {
        if (channel->unknown_0c != id) {
            continue;
        }
        if (!(channel->Flags & (AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED | AUDIO_CHANNEL_FLAG_10))) {
            break;
        }
        if (channel->Flags & AUDIO_CHANNEL_PLAYING) {
            if (channel->unknown_a0 < playing_priority) {
                playing_volume = channel->Settings.Volume.Current;
                playing_priority = channel->unknown_a0;
                playing = channel;
            } else if (channel->unknown_a0 == playing_priority) {
                unsigned int volume = channel->Settings.Volume.Current;
                if (volume < playing_volume && playing_volume - volume >= 0x666) {
                    playing_priority = channel->unknown_a0;
                    playing = channel;
                    playing_volume = volume;
                }
            }
        } else if (channel->unknown_a0 < idle_priority) {
            idle_priority = channel->unknown_a0;
            idle = channel;
        }
    }
    if (channel != 0) {
        return channel;
    }
    AudioChannel *result = idle;
    if (result == 0 || idle_priority > playing_priority) {
        result = playing;
    }
    return result;
}
