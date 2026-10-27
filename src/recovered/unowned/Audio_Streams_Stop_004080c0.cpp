// void Audio_Streams_Stop() -- 0x004080C0
// Purpose: stops every stream that is not held.
#include "shared/audio.hpp"

void Audio_Streams_Stop()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Stop(stream);
        }
    }
}
