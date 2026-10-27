// AudioChannel *__fastcall Audio_Event_Start_Channel(int priority, unsigned int flags) -- 0x00405B60
// Purpose: takes a channel from the event device for a new event, unless the
// channel is busy with something of a higher priority.
#include "shared/audio_event.hpp"

AudioChannel *__fastcall Audio_Event_Start_Channel(int priority, unsigned int flags)
{
    AudioChannel *channel = 0;

    if (Audio_Event_Device != 0) {
        channel = Audio_Device_Find_Channel(Audio_Event_Device, 1);
        if (channel != 0) {
            if ((channel->Flags & 0x15) != 0 && channel->unknown_a0 > priority) {
                return 0;
            }
            Audio_Channel_Stop(channel);
            channel->unknown_levels_94 = Audio_Global_Levels[3];
            channel->unknown_levels_9c = Audio_Global_Levels[7];
            channel->unknown_a0 = priority;
            if ((flags & 1) != 0) {
                channel->LoopCount = -1;
                return channel;
            }
            channel->LoopCount = 0;
        }
    }
    return channel;
}
