// char *__fastcall Audio_Stream_Name(AudioStreamPlayer *stream) -- 0x00407FC0
// Purpose: the stream's name.
#include "shared/audio.hpp"

char *__fastcall Audio_Stream_Name(AudioStreamPlayer *stream)
{
    return stream->Name;
}
