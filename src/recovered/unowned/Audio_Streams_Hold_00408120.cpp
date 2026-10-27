// void Audio_Streams_Hold() -- 0x00408120
// Purpose: holds every stream.
#include "shared/audio.hpp"

void Audio_Streams_Hold()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Hold(stream);
        }
    }
}
