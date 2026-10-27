// void __fastcall Audio_Stream_Wait(AudioStreamPlayer *stream) -- 0x00408010
// Purpose: keeps the game running (0x00481FB0) while the stream plays and
// its channel's volume is still moving (Audio_Stream_Is_Fading), for at
// most the volume level's MaxElapsed milliseconds.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Wait(AudioStreamPlayer *stream)
{
    __int64 end = Audio_Now() + stream->Channel->Levels.Volume.MaxElapsed;
    while (Audio_Stream_Is_Fading(stream) && (unsigned __int64)Audio_Now() < (unsigned __int64)end) {
        unknown_481fb0();
    }
}
