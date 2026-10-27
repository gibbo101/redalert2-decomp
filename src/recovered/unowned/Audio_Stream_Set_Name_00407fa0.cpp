// void __fastcall Audio_Stream_Set_Name(AudioStreamPlayer *stream, char const *name) -- 0x00407FA0
// Purpose: copies the stream's name (at most 0x4F characters).
// @ref _strncpy=007823d0
#include "shared/audio.hpp"

extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);

void __fastcall Audio_Stream_Set_Name(AudioStreamPlayer *stream, char const *name)
{
    strncpy(stream->Name, name, sizeof(stream->Name));
    stream->Name[sizeof(stream->Name) - 1] = 0;
}
