// void __fastcall Audio_Stream_Fade_Out(AudioStreamPlayer *stream) -- 0x00407FE0
// Purpose: ramps the stream channel's volume to silence.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Fade_Out(AudioStreamPlayer *stream)
{
    stream->Channel->Levels.Volume.Set_Target(0);
}
