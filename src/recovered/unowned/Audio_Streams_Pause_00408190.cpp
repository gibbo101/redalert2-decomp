// void Audio_Streams_Pause() -- 0x00408190
// Purpose: pauses every stream.
#include "shared/audio.hpp"

void Audio_Streams_Pause()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Pause(stream);
        }
    }
}
