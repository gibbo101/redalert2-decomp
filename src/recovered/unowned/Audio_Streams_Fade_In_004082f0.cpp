// void Audio_Streams_Fade_In() -- 0x004082F0
// Purpose: fades every stream in.
#include "shared/audio.hpp"

void Audio_Streams_Fade_In()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Fade_In(stream);
        }
    }
}
