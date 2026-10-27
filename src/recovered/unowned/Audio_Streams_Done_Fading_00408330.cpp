// int Audio_Streams_Done_Fading() -- 0x00408330
// Purpose: 0 while some stream is still fading, else 1.
#include "shared/audio.hpp"

int Audio_Streams_Done_Fading()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            if (Audio_Stream_Is_Fading(stream)) {
                return 0;
            }
        }
    }
    return 1;
}
