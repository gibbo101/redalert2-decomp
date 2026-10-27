// void Audio_Stop_All() -- 0x00406E20
// Purpose: stops the event channels, the events and the streams.
#include "shared/audio.hpp"

void Audio_Stop_All()
{
    if (Audio_Main_Device != 0) {
        Audio_Device_Stop_Channels(Audio_Main_Device, 1);
    }
    Audio_Events_Clear();
    Audio_Streams_Stop();
}
