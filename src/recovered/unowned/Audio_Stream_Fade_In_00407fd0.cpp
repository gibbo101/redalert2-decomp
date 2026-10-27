// void __fastcall Audio_Stream_Fade_In(AudioStreamPlayer *stream) -- 0x00407FD0
// Purpose: ramps the stream channel's volume to full.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Fade_In(AudioStreamPlayer *stream)
{
    stream->Channel->Levels.Volume.Set_Target(0x4000);
}
