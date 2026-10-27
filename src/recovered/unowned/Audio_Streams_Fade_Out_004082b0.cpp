// void Audio_Streams_Fade_Out() -- 0x004082B0
// Purpose: fades every stream out.
#include "shared/audio.hpp"

void Audio_Streams_Fade_Out()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Fade_Out(stream);
        }
    }
}
