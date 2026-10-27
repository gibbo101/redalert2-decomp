// void __fastcall Audio_Format_Init(AudioFormat *format) -- 0x004084C0
// Purpose: zero-fills the format.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void __fastcall Audio_Format_Init(AudioFormat *format)
{
    memset(format, 0, sizeof(AudioFormat));
}
