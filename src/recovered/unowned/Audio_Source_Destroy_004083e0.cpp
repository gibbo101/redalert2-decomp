// void __fastcall Audio_Source_Destroy(AudioSource *source) -- 0x004083E0
// Purpose: frees the source's data buffer and the source.
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Source_Destroy(AudioSource *source)
{
    if (source->unknown_00 != 0) {
        operator delete((void *)source->unknown_00);
    }
    operator delete(source);
}
