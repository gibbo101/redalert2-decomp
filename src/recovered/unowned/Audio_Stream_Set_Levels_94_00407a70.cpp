// void __fastcall Audio_Stream_Set_Levels_94(AudioStreamPlayer *stream, AudioLevelSet *levels) -- 0x00407A70
// Purpose: sets the level set the stream's channel combines at +0x94.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Set_Levels_94(AudioStreamPlayer *stream, AudioLevelSet *levels)
{
    stream->Channel->unknown_levels_94 = levels;
}
