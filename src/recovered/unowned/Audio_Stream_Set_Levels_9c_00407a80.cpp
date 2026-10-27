// void __fastcall Audio_Stream_Set_Levels_9c(AudioStreamPlayer *stream, AudioLevelSet *levels) -- 0x00407A80
// Purpose: sets the level set the stream's channel combines at +0x9C.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Set_Levels_9c(AudioStreamPlayer *stream, AudioLevelSet *levels)
{
    stream->Channel->unknown_levels_9c = levels;
}
