// void Audio_Streams_Release() -- 0x00408150
// Purpose: releases a hold on every stream.
#include "shared/audio.hpp"

void Audio_Streams_Release()
{
    if (Audio_Streamer_Initialized != 0) {
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            Audio_Stream_Release(stream);
        }
    }
}
